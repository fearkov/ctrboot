# Building

Needs GNU make, Python 3 and the ARM toolchain from RVCT 4.0: armcc, armasm, armlink and fromelf. On Linux and macOS they run through [wibo](https://github.com/decompals/wibo).

| Variable | | Default |
|---|---|---|
| `ARMCC_DIR` | the toolchain: the directory that holds `bin/armcc.exe`, `bin/armasm.exe`, `bin/armlink.exe` and `bin/fromelf.exe` | |
| `WIBO` | wibo; empty on Windows | `wibo` |

Set them on the command line:

```
make ARMCC_DIR=/path/to/toolchain WIBO=/path/to/wibo
```

or once in `mk/local.mk`:

```
ARMCC_DIR := /path/to/toolchain
WIBO := /path/to/wibo
```

The ROMs come out of RVCT 4.0: the functions matched so far build the same with its builds 771, 821, 865 and 902, and with ARM Compiler 4.1 build 561, but not with later 4.1 builds. Which build Nintendo used is still being worked out. A ROM can use another toolchain with `<rom>_ARMCC_DIR`.

Both ROMs are built for space, `-O3 -Ospace`: of the functions matched so far, only two come out right for speed, and say so with `#pragma Otime`.

## Images

The build needs your own boot ROMs: the functions that have no source yet, and all the data, are taken from them. Dump them from your console, with GodMode9 (the `[M:]` drive) or boot9strap (which writes them to `/boot9strap/` on the SD card), then:

```
python3 tools/images.py --boot9 boot9.bin --boot11 boot11.bin
```

Each goes to `<rom>/image/<rom>.bin` and is checked against `images.sha256`.

## Targets

| Target | |
|---|---|
| `make` | build both ROMs into `build/<rom>/<rom>.bin` |
| `make boot9`, `make boot11` | build one |
| `make check` | compare the builds with your dumps |
| `make clean` | remove `build/` |

## How a ROM is built

Each ROM has two lists:

- `<rom>.functions`: each function's address, size, ARM or Thumb, and symbol. `FUN_<address>` has no source yet; a function with source is listed under its mangled name, and its source compiles it into a section named `i.<symbol>` (armcc's `--split_sections` does that). A runtime function, from the C library or one of the helpers armcc writes itself, gives in a fifth column the names compiled code calls it by, such as `__aeabi_uldivmod` or `__ARM_common_switch8`.
- `<rom>.layout`: where the ROM is linked, and where that sits in the image. boot9 runs at `0xFFFF0000`, boot11 at its mirror at `0x00010000`.

`mk/link.awk` turns them into a scatter file that places every function with source at its own address and fills the rest with the bytes of your dump, and into a symdefs file that gives every function its address as `FUN_<address>`, so code can call any of them, with source or not, as `extern "C"` `FUN_<address>`, and the runtime functions their names, so that a 64-bit division, a table switch or a struct copy links as it is. armcc writes its `__ARM_common_` helpers into every object that uses them: once a source brings one, `names.py` lists it under its name and the build places it at its address. Every `DAT_<address>` the sources name is defined at that address too, so code reaches data, in the ROM or anywhere else, as `extern` `DAT_<address>`. armlink links the ROM and fromelf writes it out. The build stops when a function does not land at the address its list gives.

A source can also define RAM variables, zero-initialized and never with data from a ROM, when the original evidently defined them next to the function, because armcc then reaches them from one base address plus offsets. It puts them in a section named `data.<address>` or `bss.<address>` with `#pragma arm section rwdata = "data.<address>"` (or `zidata = "bss.<address>"`), and the build places that section at the address, in a region of its own that is not written to the image.

In both ROMs, the copies compiled code makes reach the C library's `memcpy`, its 12-byte wrapper around `__aeabi_memcpy`, where RVCT 4.0 calls `__aeabi_memcpy` itself (and 4.1 copies inline), so the lists give the wrapper both names.

armlink only starts a region at a multiple of 4, so Thumb functions that sit next to each other across an address 2 past a multiple of 4 share one region, where armlink orders them by name, as armcc does within a file. If two such functions do not come out in address order, the build says so.

`make check` compares each build with your dump byte for byte.

## Decompiling

A function's source is `<rom>/src/<address>.cpp`, which defines it in C++ as `FUN_<address>`: the address in its name is what places it.

| Tool | |
|---|---|
| `python3 tools/disasm.py <rom> <function>...` | a function from your dump, with what it calls and what its literal pool points at; `--xrefs` adds what calls it |
| `python3 tools/match.py <rom> <source>...` | build sources on their own, link their functions at their addresses and compare them with your dump, with a diff of what differs |
| `python3 tools/names.py` | write the names the sources give their functions into the lists and the counts into README.md; then `make check` |
| `python3 tools/twins.py <rom> <source>...` | give the functions whose code is the same but for the addresses they reach their own source |

They need [capstone](https://www.capstone-engine.org/) (`pip install capstone`). `match.py` works in a directory of its own, so it can run while other sources are being written.
