#!/usr/bin/env python3
"""Build sources on their own and compare their functions with your image.

usage: match.py <program> <source>... [--all] [--keep]

Each source is compiled with the program's flags, and every function it
defines, named FUN_<address> (C++ names keep the address in them), is linked
at its address with armlink, the rest of the program taken from your image as
in the full build. The functions are then compared with the image: OK, or a
diff of the disassembly, the image's on the - side and the build's on the +
side. --all prints the whole build of each function that differs.

It works in a directory of its own and does not read <program>.functions
for the functions it builds, so it can run while other sources are being
written, and before the list knows the new names. Functions that other
sources already match are taken from the image.

Exits 0 when every function matches.
"""
import argparse
import difflib
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from program import ADDRESS_IN_NAME, PROGRAMS, ROOT, Program, disassemble  # noqa: E402

DATA_NAME = re.compile(r"DAT_[0-9A-F]{8}")


def make_variables(names, overrides=()):
    out = subprocess.run(["make", "-s", "--no-print-directory", "-C", ROOT] + list(overrides) + [f"print-{n}" for n in names],
                         capture_output=True, text=True)
    if out.returncode:
        sys.exit(out.stderr)
    return dict(zip(names, out.stdout.split("\n")))


def run(command, what):
    out = subprocess.run(command, capture_output=True, text=True, cwd=ROOT)
    if out.returncode:
        sys.exit(f"{what} failed:\n{out.stdout}{out.stderr}")
    return out.stdout


def elf_functions(path):
    """(name, section size, thumb, section name) for each function an object
    defines in a section of its own."""
    elf = open(path, "rb").read()
    shoff = struct.unpack_from("<I", elf, 0x20)[0]
    entsize, count, shstrndx = struct.unpack_from("<HHH", elf, 0x2E)
    sections = [struct.unpack_from("<10I", elf, shoff + i * entsize) for i in range(count)]

    def string(table, at):
        start = sections[table][4] + at
        return elf[start:elf.index(b"\0", start)].decode()

    found = []
    for s in sections:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        for at in range(s[4], s[4] + s[5], 16):
            name_at, value, size, info, _, index = struct.unpack_from("<IIIBBH", elf, at)
            if info & 0xF != 2 or info >> 4 == 0 or not 0 < index < len(sections):  # global STT_FUNC
                continue
            name = string(s[6], name_at)
            section = string(shstrndx, sections[index][0])
            found.append((name, sections[index][5], bool(value & 1), section))
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("program", choices=PROGRAMS)
    parser.add_argument("sources", nargs="+")
    parser.add_argument("--all", action="store_true", help="print the whole build of each function that differs")
    parser.add_argument("--keep", action="store_true", help="keep the working directory and say where it is")
    parser.add_argument("--toolchain", metavar="DIR", help="build with this toolchain instead of the program's")
    args = parser.parse_args()
    program = Program(args.program)
    name = args.program

    sources = []
    for source in args.sources:
        path = os.path.relpath(os.path.abspath(source), ROOT)
        if not path.startswith(f"{name}/src/") or not path.endswith((".cpp", ".s")):
            sys.exit(f"{source}: sources go in {name}/src/ and end in .cpp or .s")
        if not os.path.exists(os.path.join(ROOT, path)):
            sys.exit(f"{source}: no such file")
        sources.append(path)

    work = tempfile.mkdtemp(prefix=f"match-{name}-")
    try:
        status = build_and_compare(program, sources, work, args)
    finally:
        if args.keep:
            print(f"working directory: {work}")
        else:
            shutil.rmtree(work, ignore_errors=True)
    sys.exit(status)


def build_and_compare(program, sources, work, args):
    name = program.name
    overrides = [f"{name}_ARMCC_DIR={os.path.abspath(args.toolchain)}"] if args.toolchain else []
    tools = make_variables([f"{name}_TOOLS", "ARMLINK_FLAGS"], overrides)
    wibo_bin = tools[f"{name}_TOOLS"].split()
    bin_dir = wibo_bin[-1]
    wibo = wibo_bin[:-1]
    out = os.path.join(work, name)

    # compile with the Makefile's own rules and flags
    objects = [os.path.join(out, os.path.splitext(s[len(name) + 1:])[0] + ".o") for s in sources]
    run(["make", "-s", "--no-print-directory", f"BUILD_DIR={work}"] + overrides + objects, "compiling")

    built = {}
    for source, obj in zip(sources, objects):
        for symbol, size, thumb, section in elf_functions(obj):
            if section != f"i.{symbol}":
                print(f"{source}: {symbol} is in section {section}, not i.{symbol}: build with --split_sections")
                return 1
            # a helper armcc writes into every object that uses it: armlink keeps one
            listed = program.by_runtime.get(symbol)
            if listed is not None:
                if listed.thumb != thumb:
                    print(f"{source}: {symbol} built as {'Thumb' if thumb else 'ARM'}, "
                          f"the function at 0x{listed.address:08X} is {'Thumb' if listed.thumb else 'ARM'}")
                    return 1
                built.setdefault(listed.address, (symbol, size, thumb, source))
                continue
            m = ADDRESS_IN_NAME.search(symbol)
            if symbol.startswith("FUN_"):
                print(f"{source}: {symbol} is defined extern \"C\": define it as C++, extern \"C\" "
                      f"FUN_<address> is how other code calls it")
                return 1
            if not m:
                print(f"{source}: {symbol} has no FUN_<address> in its name, and no function in the list is the "
                      f"runtime function of that name, so it has no place")
                return 1
            address = int(m.group(1), 16)
            listed = program.by_address.get(address)
            if listed is None:
                inside = program.function_at(address)
                where = f"inside {inside.name}" if inside else "not in the list"
                print(f"{source}: {symbol}: 0x{address:08X} is {where}")
                return 1
            if address in built:
                print(f"{source}: two functions for 0x{address:08X}")
                return 1
            if listed.thumb != thumb:
                print(f"{source}: {symbol} built as {'Thumb' if thumb else 'ARM'}, "
                      f"the function at 0x{address:08X} is {'Thumb' if listed.thumb else 'ARM'}")
                return 1
            built[address] = (symbol, size, thumb, source)
    if not built:
        print("no functions in the sources")
        return 1

    # the lists for this link: only these functions have source
    lines = []
    for f in program.functions:
        runtime = f" {','.join(f.runtime)}" if f.runtime else ""
        if f.address in built:
            symbol, size, thumb, _ = built[f.address]
            lines.append(f"{f.address:08X} {size} {'thumb' if thumb else 'arm'} {symbol}{runtime}")
        else:
            lines.append(f"{f.address:08X} {f.size} {'thumb' if f.thumb else 'arm'} FUN_{f.address:08X}{runtime}")
    functions_list = os.path.join(work, f"{name}.functions")
    open(functions_list, "w").write("\n".join(lines) + "\n")
    layout = os.path.join(name, f"{name}.layout")
    lists = [layout, functions_list]

    scatter = os.path.join(work, f"{name}.scat")
    open(scatter, "w").write(run(["awk", "-v", "out=scatter", "-f", "mk/link.awk"] + lists, "the scatter file")
                             + run(["awk", "-v", "out=sections", "-f", "mk/link.awk", "/dev/null"] + sources,
                                   "the RAM variables' regions"))

    gaps_dir = os.path.join(work, "gaps")
    os.makedirs(gaps_dir)
    image = program.image
    asm = []
    for line in run(["awk", "-v", "out=gaps", "-f", "mk/link.awk"] + lists, "the gaps").split("\n"):
        if not line:
            continue
        at, offset, size = line.split()
        path = os.path.join(gaps_dir, f"{at}.bin")
        open(path, "wb").write(image[int(offset):int(offset) + int(size)])
        asm.append(f"    AREA |gap.{at}|, DATA, READONLY, ALIGN=0\n    INCBIN {path}")
    gaps_s = os.path.join(work, "gaps.s")
    open(gaps_s, "w").write("\n".join(asm) + "\n    END\n")
    gaps_o = os.path.join(work, "gaps.o")
    run(wibo + [f"{bin_dir}/armasm.exe", "-o", gaps_o, gaps_s], "assembling the gaps")

    # every function as FUN_<address>, as in the full build; the functions other
    # sources match, taken from the image here, under their names; the runtime
    # functions under theirs, but for the helpers these sources bring; and the
    # data the sources name
    symdefs = ["#<SYMDEFS># ctrboot: match.py"]
    for f in program.functions:
        kind = "T" if f.thumb else "A"
        names = [f"FUN_{f.address:08X}"]
        if f.address not in built and f.has_source:
            names.append(f.name)
        names += [r for r in f.runtime if r not in names and built.get(f.address, ("",))[0] != r]
        symdefs += [f"0x{f.address:08X} {kind} {n}" for n in names]
    texts = []
    include = os.path.join(ROOT, name, "include")
    headers = [os.path.join(d, n) for d, _, ns in os.walk(include) for n in ns if n.endswith(".h")]
    for path in [os.path.join(ROOT, s) for s in sources] + headers:
        texts.append(open(path, errors="replace").read())
    for data in sorted(set(DATA_NAME.findall("\n".join(texts)))):
        symdefs.append(f"0x{data[4:]} D {data}")
    sym = os.path.join(work, f"{name}.sym")
    open(sym, "w").write("\n".join(symdefs) + "\n")

    axf = os.path.join(work, f"{name}.axf")
    mapfile = os.path.join(work, f"{name}.map")
    link = subprocess.run(wibo + [f"{bin_dir}/armlink.exe", f"--scatter={scatter}"] + args_split(tools["ARMLINK_FLAGS"])
                          + ["--map", f"--list={mapfile}", "-o", axf] + objects + [gaps_o, sym],
                          capture_output=True, text=True, cwd=ROOT)
    if link.returncode:
        print(f"linking failed:\n{link.stdout}{link.stderr}")
        return 1
    placement = subprocess.run(["awk", "-v", "out=placement", "-f", "mk/link.awk"] + lists + [mapfile],
                               capture_output=True, text=True, cwd=ROOT)
    if placement.returncode:
        print(f"functions that did not land at their address:\n{placement.stdout}")
        return 1
    parts = os.path.join(work, "parts")
    run(wibo + [f"{bin_dir}/fromelf.exe", "--bin", f"--output={parts}", axf], "fromelf")

    def built_bytes(address, size):
        for part, base, _, length in program.parts:
            if base <= address < base + length:
                path = os.path.join(parts, part) if os.path.isdir(parts) else parts
                data = open(path, "rb").read()
                return data[address - base:address - base + size]
        return b""

    unplaced = os.path.isdir(parts) and os.path.exists(os.path.join(parts, "unplaced"))
    failed = 0
    for address in sorted(built):
        symbol, size, thumb, source = built[address]
        listed = program.by_address[address]
        mine = built_bytes(address, size)
        theirs = program.read(address, listed.size)
        head = f"{name}: 0x{address:08X} {symbol}"
        if mine == theirs:
            print(f"{head}: OK")
            continue
        failed += 1
        a = disassemble(program, address, listed.size, thumb, theirs)
        b = disassemble(program, address, size, thumb, mine)
        differ = sum(1 for tag in difflib.SequenceMatcher(None, [x.text for x in a], [x.text for x in b]).get_opcodes()
                     if tag[0] != "equal")
        sizes = f"{size} bytes, the image's is {listed.size}" if size != listed.size else f"{size} bytes"
        print(f"{head}: differs ({sizes})")
        fa = [render(x, address) for x in a]
        fb = [render(x, address) for x in b]
        if args.all:
            print("\n".join(f"  {line}" for line in fb))
        print("\n".join(difflib.unified_diff(fa, fb, "image", "build", n=3, lineterm="")))
        del differ
    if unplaced:
        print(f"note: some sections are not functions in the list (strings, data, tables); "
              f"they were linked at 0x40000000, outside the image, so what points at them will differ")
    print(f"{len(built) - failed} of {len(built)} match")
    return 1 if failed else 0


def render(line, start):
    comment = f"  ; {line.comment}" if line.comment else ""
    return f"+{line.address - start:04X}  {line.text}{comment}"


def args_split(text):
    return text.split()


if __name__ == "__main__":
    main()
