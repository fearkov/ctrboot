#!/usr/bin/env python3
"""Put your own boot ROM dumps where the build looks for them.

usage: images.py --boot9 boot9.bin --boot11 boot11.bin

Each dump is copied to <program>/image/<program>.bin and checked against
images.sha256. Dump them from your console, with GodMode9 (the [M:] drive)
or boot9strap (which writes them to /boot9strap/ on the SD card).
"""
import argparse
import hashlib
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--boot9", help="your boot9.bin")
    parser.add_argument("--boot11", help="your boot11.bin")
    args = parser.parse_args()
    if not args.boot9 and not args.boot11:
        parser.error("give --boot9, --boot11 or both")

    expected = {}
    for line in open(os.path.join(ROOT, "images.sha256")):
        digest, path = line.split()
        expected[path] = digest
    failed = False
    for name, source in (("boot9", args.boot9), ("boot11", args.boot11)):
        if not source:
            continue
        path = f"{name}/image/{name}.bin"
        data = open(source, "rb").read()
        ok = hashlib.sha256(data).hexdigest() == expected[path]
        if ok:
            os.makedirs(os.path.join(ROOT, name, "image"), exist_ok=True)
            shutil.copyfile(source, os.path.join(ROOT, path))
        failed |= not ok
        print(f"{path}: {'OK' if ok else 'FAILED, not the retail ' + name + ' (not copied)'}")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
