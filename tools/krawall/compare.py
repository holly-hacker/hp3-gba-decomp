#!/usr/bin/env python3
"""Compare one third-party source's compiled sections with the ROM.

Compiles the source with the production profile (tools/c/compile_c.py;
c-file-gcc3 for Thumb C, c-file-gcc3-arm for a .arm.c, asm-file-cpp for a
.S) and compares each of its sections with the ROM bytes at the address
given. Each function is also compared with the ROM function of the same
name in functions.<ver>.cfg, wherever it is, and flagged when it is not
at the offset the section places it. Relocated words are masked, since
their values are only known after linking; `just compare` checks those.

Placements are `<section>=<rom address>`, e.g. `.text=0x08046D2C
.iwram=0x08FB0DB0`. Without any, the source's rows in regions.<ver>.txt
give them. Writes to build/<ver>/krawall-compare/.

Usage: python3 -m tools.krawall.compare <ver> <source> [<section>=<addr> ...] [--diff]
"""
import argparse
import os
import re
import subprocess
import sys

from tools.c import compile_c
from tools import buildcache
from tools.manifest import C_SECTION_DIRECTIVE, SECTIONED_DIRECTIVES, read_rows

BASE_ADDR = 0x08000000
# Sections holding code, disassembled by --diff; the others are shown as words.
CODE_SECTIONS = {".text", ".iwram", ".iwram.text"}


def directive_for(src: str) -> str:
    if src.endswith(".S"):
        return "asm-file-cpp"
    return "c-file-gcc3-arm" if src.endswith(".arm.c") else "c-file-gcc3"


def manifest_placements(ver: str, src: str) -> dict[str, int]:
    """section -> ROM address, from the source's rows in the manifest."""
    rows = [parts for _, parts in read_rows(f"regions.{ver}.txt")]
    out, name = {}, None
    for parts in rows:
        if parts[0] in SECTIONED_DIRECTIVES and parts[3] == src:
            name = parts[4]
            out[parts[5] if len(parts) > 5 else ".text"] = int(parts[1], 16)
    for parts in rows:
        if parts[0] == C_SECTION_DIRECTIVE and parts[3] == name:
            out[parts[4]] = int(parts[1], 16)
    return out


def cfg_addresses(ver: str) -> dict[str, int]:
    out = {}
    with open(f"functions.{ver}.cfg") as f:
        for line in f:
            parts = line.split("#", 1)[0].split()
            if len(parts) == 3 and parts[0] in ("thumb_func", "arm_func"):
                out[parts[2]] = int(parts[1], 16)
    return out


def run(*args: str) -> str:
    return subprocess.run(args, capture_output=True, text=True, check=True).stdout


def section_info(obj: str, section: str):
    """(bytes, relocated offsets, [(offset, size, name)] of its functions)."""
    out = os.path.join(os.path.dirname(obj), "section.bin")
    subprocess.run(["arm-none-eabi-objcopy", "-O", "binary", "-j", section, obj, out], check=True)
    with open(out, "rb") as f:
        data = f.read()
    relocated = set()
    for line in run("arm-none-eabi-objdump", "-r", "-j", section, obj).splitlines():
        m = re.match(r"([0-9a-f]{8}) ", line)
        if m:
            relocated.update(range(int(m.group(1), 16), int(m.group(1), 16) + 4))
    functions = []
    for line in run("arm-none-eabi-objdump", "-t", obj).splitlines():
        m = re.match(r"([0-9a-f]{8}) .{6}F (\S+)\s+([0-9a-f]{8}) (\S+)$", line)
        if m and m.group(2) == section:
            functions.append((int(m.group(1), 16), int(m.group(3), 16), m.group(4)))
    return data, relocated, sorted(functions)


def disassemble(data: bytes, thumb: bool, code: bool) -> list[str]:
    if not code:
        return [data[i:i + 4].hex() for i in range(0, len(data), 4)]
    path = os.path.join(OUT, "dis.bin")
    with open(path, "wb") as f:
        f.write(data)
    text = run("arm-none-eabi-objdump", "-D", "-b", "binary", "-marm",
               *(["-M", "force-thumb"] if thumb else []), path)
    return [line.split("\t", 1)[1] for line in text.splitlines()
            if re.match(r"\s+[0-9a-f]+:\t", line)]


def main() -> None:
    global OUT
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("ver", choices=["us", "jp"])
    ap.add_argument("source")
    ap.add_argument("placements", nargs="*", metavar="section=addr")
    ap.add_argument("--diff", action="store_true",
                    help="show differing sections side by side")
    args = ap.parse_args()

    places = {}
    for p in args.placements:
        section, _, addr = p.partition("=")
        places[section] = int(addr, 16)
    if not places:
        places = manifest_placements(args.ver, args.source)
        if not places:
            sys.exit(f"{args.source} has no rows in regions.{args.ver}.txt; give section=addr placements")

    OUT = f"build/{args.ver}/krawall-compare"
    os.makedirs(OUT, exist_ok=True)
    directive = directive_for(args.source)
    asm, obj = os.path.join(OUT, "object.s"), os.path.join(OUT, "object.o")
    compile_c.compile_sectioned(args.source, asm, compile_c.agbcc_prefix(),
                                buildcache.tool_digest(), directive)
    subprocess.run(["arm-none-eabi-as", "-mcpu=arm7tdmi", asm, "-o", obj], check=True)
    with open(f"baserom.{args.ver}.gba", "rb") as f:
        rom = f.read()

    thumb = directive == "c-file-gcc3"
    named = cfg_addresses(args.ver)
    ok = True
    for section, addr in places.items():
        data, relocated, functions = section_info(obj, section)
        target = rom[addr - BASE_ADDR:addr - BASE_ADDR + len(data)]
        differ = [i for i in range(len(data)) if i not in relocated and data[i] != target[i]]
        state = "MATCH" if not differ else f"{len(differ)} bytes differ, first at +{differ[0]:#x}"
        print(f"{section}: {len(data):#x} bytes at {addr:#010x}: {state}")
        for offset, size, name in functions:
            # The cfg names ROM copies of RAM code at their ROM address.
            where = named.get(name, addr + offset)
            rom_fn = rom[where - BASE_ADDR:where - BASE_ADDR + size]
            bad = sum(1 for i in range(size) if offset + i not in relocated
                      and data[offset + i] != rom_fn[i])
            moved = "" if where == addr + offset else f"  (ROM has it at {where:#010x})"
            print(f"  {name:32s} {size:#6x}  "
                  f"{'match' if not bad else f'{100 * (size - bad) / size:.0f}%'}{moved}")
        if differ:
            ok = False
            if args.diff:
                code = section in CODE_SECTIONS
                rom_lines = disassemble(target, thumb and section == ".text", code)
                own_lines = disassemble(data, thumb and section == ".text", code)
                for i in range(max(len(rom_lines), len(own_lines))):
                    a = rom_lines[i] if i < len(rom_lines) else ""
                    b = own_lines[i] if i < len(own_lines) else ""
                    mark = " " if a.split("@")[0].split() == b.split("@")[0].split() else "|"
                    print(f"    {a[:48]:48s} {mark} {b[:48]}")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
