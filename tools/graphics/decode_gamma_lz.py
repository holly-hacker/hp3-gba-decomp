#!/usr/bin/env python3
"""Decode a DecompressGammaLz-compressed resource blob using the game's own
decompressor -- executed via the Unicorn CPU emulator against the real
ARM-mode ROM bytes, rather than a hand-reimplementation, so it can't
silently drift from actual game behavior. See docs/formats/graphics.md's
"The DecompressGammaLz codec, decoded" section for the full bit-level algorithm
writeup and how this was verified (exact size match against 7 real
level-table resource pointers).

Every real DecompressGammaLz resource decoded so far has turned out to be GBA BG
tilemap/screen-entry data, not text or pixel data -- see
docs/formats/graphics.md and docs/formats/text.md for what that does
and doesn't tell us about where dialog text or real palettes live.

Usage: decode_gamma_lz.py <ver> <hex addr>
  <hex addr> is the ROM address of the resource's 4-byte outer header
  (type/size word) -- e.g. a level-table pointer field, such as
  0x08658a6c (level-table entry 0's +0x00 field, see graphics.md).
Writes raw decoded bytes to stdout.
"""
import struct
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_ARM, UC_PROT_READ, UC_PROT_WRITE, UC_PROT_EXEC, UcError
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_SP, UC_ARM_REG_LR

ROM_BASE = 0x08000000

# The codec's ARM-mode source bytes in the ROM (us version) -- the game
# itself copies this to IWRAM 0x03002ACC at runtime; see
# docs/formats/text.md sec 6. Not yet confirmed at the same address in
# the jp ROM -- ver is accepted as a parameter for when that's checked.
CODEC_ADDR = {"us": 0x080005EC}

# Emulator scratch memory, chosen clear of the mapped ROM image.
SCRATCH_BASE = 0x03000000
STACK_ADDR = 0x03000400
OUT_SIZE_ADDR = 0x03000800
OUT_BUF_ADDR = 0x03010000


def decode_gamma_lz(rom: bytes, hdr_addr: int, codec_addr: int) -> bytes:
    """hdr_addr is the ROM address of the resource's 4-byte outer header
    (type nibble + 24-bit decompressed size), same shape as a level-table
    pointer field."""
    off = hdr_addr - ROM_BASE
    header = rom[off:off + 4]
    extra_pass = bool(header[0] & 0x80)  # sub_0801DF48 delta-decode pass,
    # applied by the *caller* after the codec returns -- not part of the
    # codec itself. See docs/formats/graphics.md.
    decompressed_size = header[1] | (header[2] << 8) | (header[3] << 16)

    mu = Uc(UC_ARCH_ARM, UC_MODE_ARM)
    mu.mem_map(ROM_BASE, 0x01000000, UC_PROT_READ | UC_PROT_EXEC)
    mu.mem_write(ROM_BASE, rom)
    mu.mem_map(SCRATCH_BASE, 0x1000, UC_PROT_READ | UC_PROT_WRITE)
    out_cap = max((decompressed_size + 0xFFF) & ~0xFFF, 0x1000)
    mu.mem_map(OUT_BUF_ADDR, out_cap, UC_PROT_READ | UC_PROT_WRITE)
    mu.mem_write(OUT_SIZE_ADDR, b"\x00" * 4)

    mu.reg_write(UC_ARM_REG_R0, hdr_addr + 4)  # skip outer 4-byte header
    mu.reg_write(UC_ARM_REG_R1, OUT_BUF_ADDR)  # dst
    mu.reg_write(UC_ARM_REG_R2, OUT_SIZE_ADDR)  # &out_size
    mu.reg_write(UC_ARM_REG_SP, STACK_ADDR)
    mu.reg_write(UC_ARM_REG_LR, 0x1)  # invalid return address -- deliberately
    # faults back out of emu_start once the codec returns, caught below.
    try:
        mu.emu_start(codec_addr, 0, count=50_000_000)
    except UcError:
        pass

    size = struct.unpack_from("<I", mu.mem_read(OUT_SIZE_ADDR, 4))[0]
    out = bytes(mu.mem_read(OUT_BUF_ADDR, size))
    return _apply_delta_pass(out) if extra_pass else out


def _apply_delta_pass(buf: bytes) -> bytes:
    """sub_0801DF48/sub_0801DF6C: an in-place running sum over the decoded
    buffer as u16[] -- the codec's raw output is itself delta-coded when
    the outer header's extra-pass bit is set."""
    n = len(buf) // 2
    vals = list(struct.unpack(f"<{n}H", buf[:n * 2]))
    for i in range(1, n):
        vals[i] = (vals[i] + vals[i - 1]) & 0xFFFF
    return struct.pack(f"<{n}H", *vals) + buf[n * 2:]


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    ver, addr_s = sys.argv[1], sys.argv[2]
    if ver not in CODEC_ADDR:
        sys.exit(f"codec address not yet confirmed for ver={ver!r}")
    addr = int(addr_s, 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    out = decode_gamma_lz(rom, addr, CODEC_ADDR[ver])
    sys.stdout.buffer.write(out)


if __name__ == "__main__":
    main()
