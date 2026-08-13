#!/usr/bin/env python3
"""Statically enumerate real OBJ palettes reachable through
sub_08001528(type, x, y, resource_ptr) -- the generic pooled-object
spawner documented in docs/formats/graphics.md ("Real, uncompressed
palettes" / "sub_08001528's call chain, traced"). Every resource_ptr
passed through this call is unconditionally treated by sub_08030978 as
a 2-byte header followed by 15 raw BGR555 colors (`resource_ptr+2`,
queued for a 15-color upload) -- confirmed by tracing the call chain
down to the real vblank DMA flush, and cross-checked against three
independently-found-live palettes matching byte-for-byte.

This requires build/us/full_disasm.s (gbadisasm's full matching
disassembly -- regenerate locally with `just disasm us` if missing;
not committed, see regions.us.txt's header comment).

Finds every `bl sub_08001528` call site, then walks backward through
the enclosing function for the last assignment to r3 (the resource_ptr
argument) -- either a direct `ldr r3, =literal` or a short register-copy
chain (`mov r3, rN` back to wherever rN was itself loaded). Call sites
where r3 is set some other way (loaded from a struct field, computed at
runtime, passed in from a caller) are reported as unresolved -- this is
a static, best-effort trace, not a full dataflow analysis.

Usage: find_object_palettes.py <ver>
Prints one line per call site: address, resolved resource_ptr (or
UNRESOLVED), and distinct-color count (a resolved pointer whose 15
"colors" are mostly identical is more likely a false trace than a real
palette -- inspect low-distinct-count hits before trusting them).
"""
import re
import struct
import sys

ROM_BASE = 0x08000000
ROM_END = 0x08FFFFFF


def build_literal_pool(lines: list[str]) -> dict[str, int]:
    pool = {}
    for l in lines:
        m = re.match(r"(_[0-9A-Fa-f]+):\s*\.4byte\s+(0x[0-9A-Fa-f]+)", l.strip())
        if m:
            pool[m.group(1)] = int(m.group(2), 16)
    return pool


def trace_reg(lines: list[str], pool: dict[str, int], idx: int, reg: str, depth: int = 0):
    if depth > 6:
        return None
    for j in range(idx - 1, max(0, idx - 40), -1):
        l = lines[j].strip()
        m = re.match(rf"ldr {reg},\s*(_[0-9A-Fa-f]+)", l)
        if m:
            return pool.get(m.group(1))
        m2 = re.match(rf"(?:mov|movs|adds|lsls) {reg},\s*(r\d+)", l)
        if m2 and m2.group(1) != reg:
            return trace_reg(lines, pool, j, m2.group(1), depth + 1)
        if re.match(rf"(movs|adds|subs|mov) {reg},", l):
            return None  # reassigned via immediate/other op -- give up
    return None


def enclosing_function(lines: list[str], idx: int) -> str | None:
    for j in range(idx, max(0, idx - 2000), -1):
        m = re.match(r"sub_([0-9A-Fa-f]+):", lines[j].strip())
        if m:
            return "sub_" + m.group(1)
    return None


def decode_palette_colors(rom: bytes, addr: int, n: int = 15) -> list[tuple[int, int, int]]:
    off = addr - ROM_BASE + 2  # skip 2-byte header
    colors = []
    for i in range(n):
        v = struct.unpack_from("<H", rom, off + i * 2)[0]
        colors.append(((v & 0x1F) * 8, ((v >> 5) & 0x1F) * 8, ((v >> 10) & 0x1F) * 8))
    return colors


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    with open(f"build/{ver}/full_disasm.s") as f:
        lines = f.readlines()
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()

    pool = build_literal_pool(lines)
    call_sites = [i for i, l in enumerate(lines) if "bl sub_08001528" in l]

    for idx in call_sites:
        func = enclosing_function(lines, idx)
        val = trace_reg(lines, pool, idx, "r3")
        if val is None or not (ROM_BASE <= val <= ROM_END):
            print(f"line {idx + 1:8d}  {func or '?':16s}  UNRESOLVED")
            continue
        colors = decode_palette_colors(rom, val)
        distinct = len(set(colors))
        print(f"line {idx + 1:8d}  {func or '?':16s}  0x{val:08x}  distinct_colors={distinct}/15")


if __name__ == "__main__":
    main()
