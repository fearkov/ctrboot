#!/usr/bin/env python3
"""Give a matched function's twins their source.

usage: twins.py <program> <source>... [--dry-run]

The programs share library code, so the same function often sits in several
of them, or twice in one, calling other addresses and pointing at other data.
For each function the sources define, this finds the functions whose code is
the same but for those addresses, writes each one's source with its
FUN_<address> and DAT_<address> names changed to the twin's, checks it with
tools/match.py and keeps it only when it matches.

The fingerprints of every program's functions are kept in build/twins.json
and made again when an image or a list changes.
"""
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import elf_functions  # noqa: E402
from program import ADDRESS_IN_NAME, PROGRAMS, ROOT, Program, disassemble  # noqa: E402

CACHE = os.path.join(ROOT, "build", "twins.json")
NAME = re.compile(r"\b(FUN|DAT|Unk)_([0-9A-F]{8})\b")


def is_address(program, value):
    return program.part_of(value & ~1) is not None or value >= 0x00100000


def shape(program, f):
    """The function's instructions with the addresses it reaches taken out, and
    those addresses in order: (call and branch targets, literal words)."""
    lines, targets, words = [], [], []
    for line in disassemble(program, f.address, f.size, f.thumb):
        if line.text.startswith(".word"):
            value = int(line.text.split()[1], 16)
            if is_address(program, value):
                lines.append(".word ADDRESS")
                words.append(value)
            else:
                lines.append(line.text)
        elif line.target is not None and not f.address <= line.target < f.end:
            lines.append(line.text.split()[0] + " OUT")
            targets.append(line.target)
        elif line.target is not None:
            lines.append(f"{line.text.split()[0]} +{line.target - f.address:X}")
        elif "pc, #" in line.text:
            lines.append(line.text.split(",")[0] + ", POOL")
        else:
            lines.append(line.text)
    return hashlib.sha1("\n".join(lines).encode()).hexdigest(), targets, words


def stamp():
    parts = []
    for p in PROGRAMS:
        for path in (f"{p}/{p}.functions", f"{p}/{p}.layout", f"{p}/image/{p}.bin"):
            full = os.path.join(ROOT, path)
            parts.append(f"{path}:{os.path.getmtime(full) if os.path.exists(full) else 0}")
    return hashlib.sha1("\n".join(parts).encode()).hexdigest()


def fingerprints():
    """{program: {address: [hash, targets, words]}}"""
    now = stamp()
    if os.path.exists(CACHE):
        cached = json.load(open(CACHE))
        if cached.get("stamp") == now:
            return cached["programs"]
    found = {}
    for p in PROGRAMS:
        program = Program(p)
        found[p] = {f"{f.address:08X}": list(shape(program, f)) for f in program.functions}
    os.makedirs(os.path.dirname(CACHE), exist_ok=True)
    temporary = f"{CACHE}.{os.getpid()}"
    json.dump({"stamp": now, "programs": found}, open(temporary, "w"))
    os.replace(temporary, CACHE)
    return found


def renames(mine, theirs):
    """How names change from one twin to the other, or None if one address
    would have to become two."""
    table = {}
    for kind, a, b in [("FUN", x, y) for x, y in zip(mine[1], theirs[1])] + \
                      [("ANY", x, y) for x, y in zip(mine[2], theirs[2])]:
        for prefix in (["FUN", "DAT"] if kind == "ANY" else ["FUN"]):
            old, new = f"{prefix}_{a & ~1 if prefix == 'FUN' else a:08X}", \
                f"{prefix}_{b & ~1 if prefix == 'FUN' else b:08X}"
            if table.get(old, new) != new:
                return None
            table[old] = new
    return table


def with_state(text, program, thumb):
    """The source with the #pragma that builds it ARM or Thumb in that program."""
    mk = open(os.path.join(ROOT, program, f"{program}.mk")).read()
    default_thumb = "--thumb" in mk
    text = re.sub(r"^#pragma (arm|thumb)\n", "", text, flags=re.M)
    if thumb == default_thumb:
        return text
    return f"#pragma {'thumb' if thumb else 'arm'}\n{text}"


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("program", choices=PROGRAMS)
    parser.add_argument("sources", nargs="+")
    parser.add_argument("--dry-run", action="store_true", help="say which twins there are, write nothing")
    args = parser.parse_args()
    prints = fingerprints()

    written = 0
    for source in args.sources:
        path = os.path.relpath(os.path.abspath(source), ROOT)
        text = open(os.path.join(ROOT, path)).read()
        obj = os.path.join(ROOT, "build", args.program, os.path.splitext(path[len(args.program) + 1:])[0] + ".o")
        subprocess.run(["make", "-s", "--no-print-directory", os.path.relpath(obj, ROOT)], cwd=ROOT, check=True)
        defined = [ADDRESS_IN_NAME.search(symbol).group(1) for symbol, _, _, _ in elf_functions(obj)
                   if ADDRESS_IN_NAME.search(symbol)]
        if len(defined) != 1:
            print(f"{path}: twins.py takes sources with one function, this one has {len(defined)}")
            continue
        address = defined[0]
        mine = prints[args.program].get(address)
        if mine is None:
            print(f"{path}: 0x{address} is not in {args.program}.functions")
            continue
        for other in PROGRAMS:
            for twin, theirs in sorted(prints[other].items()):
                if theirs[0] != mine[0] or (other == args.program and twin == address):
                    continue
                target = os.path.join(other, "src", f"{twin}.cpp")
                where = f"{path} -> {other}: 0x{twin}"
                if os.path.exists(os.path.join(ROOT, target)):
                    print(f"{where}: has source already")
                    continue
                if Program(other).by_address[int(twin, 16)].has_source:
                    print(f"{where}: has source already")
                    continue
                table = renames(mine, theirs)
                if table is None:
                    print(f"{where}: the addresses do not map one to one")
                    continue
                table[f"FUN_{address}"] = f"FUN_{twin}"
                table[f"Unk_{address}"] = f"Unk_{twin}"
                # a tail call into the next function, which armlink makes a nop
                size = Program(args.program).by_address[int(address, 16)].size
                table.setdefault(f"FUN_{int(address, 16) + size:08X}", f"FUN_{int(twin, 16) + size:08X}")
                unknown = sorted({m.group(0) for m in NAME.finditer(text)
                                  if m.group(1) != "Unk" and m.group(0) not in table})
                if unknown:
                    print(f"{where}: no twin for {', '.join(unknown)}")
                    continue
                if args.dry_run:
                    print(f"{where}: twin")
                    continue
                os.makedirs(os.path.join(ROOT, other, "src"), exist_ok=True)
                new = NAME.sub(lambda m: table.get(m.group(0), m.group(0)), text)
                new = with_state(new, other, Program(other).by_address[int(twin, 16)].thumb)
                open(os.path.join(ROOT, target), "w").write(new)
                check = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "match.py"), other, target],
                                       cwd=ROOT, capture_output=True, text=True)
                if check.returncode == 0:
                    print(f"{where}: OK, {target}")
                    written += 1
                else:
                    os.remove(os.path.join(ROOT, target))
                    print(f"{where}: does not match")
    print(f"{written} twins written")


if __name__ == "__main__":
    main()
