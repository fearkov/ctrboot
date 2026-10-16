#!/usr/bin/env python3
"""Disassemble functions from your image, the way the lists describe them.

usage: disasm.py <program> <function>... [--xrefs]
       disasm.py <program> --range <start> <end> [--thumb]

A function is its address or its name. Calls and branches out of the function
are shown with the name of their target, and the words that PC-relative loads
read with what they point at: a function, a string, a part of the image.
--xrefs also lists the functions that call or point at each one.

Needs capstone (pip install capstone).
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from program import PROGRAMS, Program, disassemble, format_lines  # noqa: E402


def references(program):
    """{address: set of addresses of the functions that call or point at it}."""
    callers = {}
    for f in program.functions:
        for line in disassemble(program, f.address, f.size, f.thumb):
            targets = []
            if line.target is not None and not f.address <= line.target < f.end:
                targets.append(line.target)
            if line.text.startswith(".word"):
                targets.append(int(line.text.split()[1], 16) & ~1)
            for t in targets:
                if t in program.by_address:
                    callers.setdefault(t, set()).add(f.address)
    return callers


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("program", choices=PROGRAMS)
    parser.add_argument("functions", nargs="*")
    parser.add_argument("--range", nargs=2, metavar=("START", "END"))
    parser.add_argument("--thumb", action="store_true", help="with --range: decode as Thumb")
    parser.add_argument("--xrefs", action="store_true", help="list who calls or points at each function")
    args = parser.parse_args()
    program = Program(args.program)

    if args.range:
        start, end = (int(x, 16) for x in args.range)
        print("\n".join(format_lines(disassemble(program, start, end - start, args.thumb))))
        return

    callers = references(program) if args.xrefs else {}
    for i, what in enumerate(args.functions):
        f = program.find(what)
        if i:
            print()
        print(f"# {f.name}  {args.program}  {'thumb' if f.thumb else 'arm'}  {f.size} bytes  "
              f"0x{f.address:08X}-0x{f.end:08X}")
        if args.xrefs:
            names = sorted(program.by_address[a].name for a in callers.get(f.address, ()))
            print(f"# referenced by: {', '.join(names) if names else 'nothing found'}")
        print("\n".join(format_lines(disassemble(program, f.address, f.size, f.thumb))))


if __name__ == "__main__":
    main()
