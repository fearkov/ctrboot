"""A program's lists and image, and a disassembler that knows them.

Shared by tools/disasm.py and tools/match.py. Needs capstone
(pip install capstone).
"""
import bisect
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGRAMS = ["boot9", "boot11"]
ADDRESS_IN_NAME = re.compile(r"FUN_([0-9A-F]{8})")


class Function:
    def __init__(self, address, size, thumb, name):
        self.address = address
        self.size = size
        self.thumb = thumb
        self.name = name

    @property
    def end(self):
        return self.address + self.size

    @property
    def has_source(self):
        return not self.name.startswith("FUN_")


class Program:
    def __init__(self, name, functions_path=None):
        self.name = name
        self.dir = os.path.join(ROOT, name)
        self.parts = []
        for fields in _lines(os.path.join(self.dir, f"{name}.layout")):
            part, base, offset, size = fields
            self.parts.append((part, int(base, 16), int(offset, 16), int(size, 16)))
        self.functions = []
        for fields in _lines(functions_path or os.path.join(self.dir, f"{name}.functions")):
            address, size, state, symbol = fields
            self.functions.append(Function(int(address, 16), int(size), state == "thumb", symbol))
        self.functions.sort(key=lambda f: f.address)
        self.starts = [f.address for f in self.functions]
        self.by_address = {f.address: f for f in self.functions}
        self._image = None

    @property
    def image(self):
        if self._image is None:
            path = os.path.join(self.dir, "image", f"{self.name}.bin")
            if not os.path.exists(path):
                raise SystemExit(f"{path} is missing: put your dumps in place first: tools/images.py, see BUILDING.md")
            self._image = open(path, "rb").read()
        return self._image

    def part_of(self, address):
        for part in self.parts:
            if part[1] <= address < part[1] + part[3]:
                return part
        return None

    def offset_of(self, address):
        part = self.part_of(address)
        return None if part is None else part[2] + address - part[1]

    def read(self, address, size, image=None):
        offset = self.offset_of(address)
        if offset is None:
            return None
        return (image or self.image)[offset:offset + size]

    def word(self, address):
        data = self.read(address, 4)
        return int.from_bytes(data, "little") if data and len(data) == 4 else None

    def function_at(self, address):
        """The function that contains address, or None."""
        i = bisect.bisect_right(self.starts, address) - 1
        if i >= 0 and address < self.functions[i].end:
            return self.functions[i]
        return None

    def find(self, what):
        """A function by address (hex, with or without 0x) or by name."""
        for f in self.functions:
            if f.name == what:
                return f
        try:
            address = int(what, 16)
        except ValueError:
            raise SystemExit(f"{self.name}: no function {what}")
        f = self.function_at(address)
        if f is None:
            raise SystemExit(f"{self.name}: no function at {address:08X}")
        return f

    def describe(self, value):
        """What a 32-bit value points at, if anything: a function or a place in the image."""
        f = self.by_address.get(value & ~1)
        if f is not None and (value & 1) == f.thumb:
            return f.name
        part = self.part_of(value)
        if part is None:
            return None
        f = self.function_at(value)
        if f is not None and part[0] not in ("rodata", "data"):
            return f"{f.name}+0x{value - f.address:X}"
        text = string_at(self, value)
        if text is not None:
            return f"{part[0]} {text}"
        return part[0]


def _lines(path):
    for line in open(path):
        if line.startswith("#") or not line.strip():
            continue
        yield line.split()


def string_at(program, address):
    data = program.read(address, 64)
    if not data:
        return None
    end = data.find(b"\0")
    if end < 2:
        return None
    text = data[:end]
    if all(32 <= c < 127 or c in (9, 10, 13) for c in text):
        return '"' + text.decode().replace("\n", "\\n") + '"'
    return None


_engines = {}


def _engine(thumb):
    if thumb not in _engines:
        from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs
        md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
        md.detail = True
        _engines[thumb] = md
    return _engines[thumb]


BRANCH = re.compile(r"^(b|bl|blx)(eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?$")


class Line:
    """One instruction or data word: address, bytes, text, comment."""

    def __init__(self, address, data, text, comment="", target=None):
        self.address = address
        self.data = data
        self.text = text
        self.comment = comment
        self.target = target


def disassemble(program, address, size, thumb, data=None):
    """Lines for size bytes at address. Words that PC-relative loads read are
    shown as data, with what they point at. data replaces the image's bytes."""
    if data is None:
        data = program.read(address, size)
    from capstone.arm import ARM_OP_IMM, ARM_OP_MEM, ARM_REG_PC
    md = _engine(thumb)
    pool = {}
    lines = []

    def decode(at):
        chunk = data[at - address:at - address + 4]
        for insn in md.disasm(chunk, at, 1):
            return insn
        return None

    # first pass: find the literal pool words
    at = address
    while at < address + size:
        if at in pool:
            at += 4
            continue
        insn = decode(at)
        if insn is None:
            at += 2 if thumb else 4
            continue
        for op in insn.operands:
            if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC and op.mem.index == 0 \
                    and insn.mnemonic.startswith("ldr"):
                base = (at + 4) & ~3 if thumb else at + 8
                word = base + op.mem.disp
                if address <= word < address + size:
                    pool[word] = insn.mnemonic
        at += insn.size

    at = address
    while at < address + size:
        if at in pool and at + 4 <= address + size:
            raw = data[at - address:at - address + 4]
            value = int.from_bytes(raw, "little")
            what = program.describe(value)
            lines.append(Line(at, raw, f".word 0x{value:08X}", what or ""))
            at += 4
            continue
        insn = decode(at)
        if insn is None or (at + insn.size > address + size):
            step = 2 if thumb else 4
            raw = data[at - address:at - address + step]
            if len(raw) == 4:
                lines.append(Line(at, raw, f".word 0x{int.from_bytes(raw, 'little'):08X}"))
            elif len(raw) == 2:
                lines.append(Line(at, raw, f".hword 0x{int.from_bytes(raw, 'little'):04X}"))
            else:
                lines.append(Line(at, raw, ".byte " + ", ".join(f"0x{b:02X}" for b in raw)))
            at += len(raw) or step
            continue
        text = f"{insn.mnemonic:<8} {insn.op_str}".rstrip()
        comment = ""
        target = None
        if BRANCH.match(insn.mnemonic) and insn.operands and insn.operands[0].type == ARM_OP_IMM:
            target = insn.operands[0].imm & 0xFFFFFFFF
            if address <= target < address + size:
                comment = f"+0x{target - address:X}"
            else:
                f = program.function_at(target)
                if f is not None:
                    comment = f.name if f.address == target else f"{f.name}+0x{target - f.address:X}"
        else:
            for op in insn.operands:
                if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC and op.mem.index == 0:
                    base = (at + 4) & ~3 if thumb else at + 8
                    word = base + op.mem.disp
                    if address <= word < address + size and word + 4 <= address + size:
                        value = int.from_bytes(data[word - address:word - address + 4], "little")
                    else:
                        value = program.word(word)
                    if value is not None:
                        what = program.describe(value)
                        comment = f"=0x{value:08X}" + (f" {what}" if what else "")
            if not comment and insn.mnemonic in ("adr", "add", "adds") and "pc" in insn.op_str.split(", ")[1:2]:
                imm = [op.imm for op in insn.operands if op.type == ARM_OP_IMM]
                if imm:
                    base = (at + 4) & ~3 if thumb else at + 8
                    value = base + imm[0]
                    what = program.describe(value)
                    comment = f"=0x{value:08X}" + (f" {what}" if what else "")
        lines.append(Line(at, bytes(insn.bytes), text, comment, target))
        at += insn.size
    return lines


def format_lines(lines, start=None):
    out = []
    for line in lines:
        where = f"{line.address:08X}" if start is None else f"+{line.address - start:04X}"
        raw = line.data.hex()
        comment = f"  ; {line.comment}" if line.comment else ""
        out.append(f"{where}  {raw:<8}  {line.text}{comment}")
    return out
