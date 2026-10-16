#!/usr/bin/env python3
"""Write the names the sources give their functions into the lists.

usage: names.py [<program>...]

Compiles each program's sources and, in <program>.functions, gives every
function a source defines its name from the object (the name holds
FUN_<address>, which places it), and every other function back its
FUN_<address>. Then counts what has source into the table in README.md.
Run it after adding or renaming functions, then make check.
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import elf_functions  # noqa: E402
from program import ADDRESS_IN_NAME, PROGRAMS, ROOT, Program  # noqa: E402


def sources_of(name):
    found = []
    for directory, _, files in os.walk(os.path.join(ROOT, name, "src")):
        for f in files:
            if f.endswith((".cpp", ".s")):
                found.append(os.path.relpath(os.path.join(directory, f), ROOT))
    return sorted(found)


def update(name):
    program = Program(name)
    sources = sources_of(name)
    objects = [os.path.join("build", name, os.path.splitext(s[len(name) + 1:])[0] + ".o") for s in sources]
    if objects:
        out = subprocess.run(["make", "-s", "--no-print-directory", "-j8"] + objects, cwd=ROOT,
                             capture_output=True, text=True)
        if out.returncode:
            sys.exit(f"{name}: compiling failed:\n{out.stdout}{out.stderr}")
    names = {}
    for source, obj in zip(sources, objects):
        for symbol, size, thumb, section in elf_functions(os.path.join(ROOT, obj)):
            m = ADDRESS_IN_NAME.search(symbol)
            if not m or symbol.startswith("FUN_"):
                print(f"{name}: {source}: {symbol} has no place (see tools/match.py)")
                continue
            address = int(m.group(1), 16)
            if address not in program.by_address:
                print(f"{name}: {source}: {symbol}: no function at 0x{address:08X} in the list")
                continue
            if address in names:
                print(f"{name}: {source}: {symbol}: 0x{address:08X} is also {names[address]}")
                continue
            names[address] = symbol

    path = os.path.join(ROOT, name, f"{name}.functions")
    lines = open(path).read().split("\n")
    changed = 0
    for i, line in enumerate(lines):
        if line.startswith("#") or not line.strip():
            continue
        address, size, state, symbol = line.split()
        wanted = names.get(int(address, 16), f"FUN_{address}")
        if wanted != symbol:
            lines[i] = f"{address} {size} {state} {wanted}"
            changed += 1
    open(path, "w").write("\n".join(lines))
    print(f"{name}: {len(names)} of {len(program.functions)} functions have source, {changed} names changed")
    return len(names), len(program.functions)


def main():
    programs = sys.argv[1:] or PROGRAMS
    for p in programs:
        if p not in PROGRAMS:
            sys.exit(f"no program {p}")
    counts = {p: update(p) for p in programs}

    readme = os.path.join(ROOT, "README.md")
    text = open(readme).read()
    for p, (done, total) in counts.items():
        text = re.sub(rf"(\| `{p}` \|[^\n]*\| )\d+ / \d+ \|", rf"\g<1>{done} / {total} |", text)
    open(readme, "w").write(text)


if __name__ == "__main__":
    main()
