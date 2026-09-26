#!/usr/bin/env python3
"""Decode a DecompressLzRle-compressed resource blob using the game's own
decompressor -- executed via the Unicorn CPU emulator against the real
ARM-mode ROM bytes, same approach as tools/graphics/decode_gamma_lz.py (not a
hand-reimplementation -- the codec's halfword-aligned, parity-tracked
copy logic is intricate enough that a hand port risks a subtle,
plausible-looking bug; cf. the mid-token cutoff that a hand-written
standard-BIOS RLE decoder gets wrong, in tools/graphics/decode_bios.py).

Unlike DecompressGammaLz, this resource's outer-header convention (if any) isn't
independently understood -- the source address used here is exactly
what the game's own code passes to the codec at its entry point (r0),
captured live via an mGBA breakpoint on the codec's IWRAM entry
(0x030028D4) while the main-menu wand cursor's animated glow tiles were
loading. See docs/formats/graphics.md's "The wand cursor sprite"
section for how these addresses were found and how this decoder was
verified: 0x080bcbd0 decodes to a 128-byte, exact byte-for-byte match
against the four wand-glow tiles read live from OBJ tile VRAM (real
game memory, not a guess) -- and the codec itself stops writing at
exactly that 128-byte boundary (everything past it in the output
buffer is untouched scratch/zero), so the true output length is
self-evident from the result, not assumed.

Usage: decode_lz_rle.py <ver> <hex addr>
  <hex addr> is the exact ROM source address the game passes in r0 at
  the codec's entry point -- e.g. 0x080bcbd0 (one of the wand glow's
  animation-frame sources). NOT a "+4 skip a header" address like
  decode_gamma_lz.py -- no outer-header handling is done here at all.
Writes raw decoded bytes to stdout (fixed-size buffer, see OUT_CAP;
trailing bytes past the codec's real output are whatever was in the
scratch buffer, i.e. zero -- inspect the output for a plausible stop
point, this doesn't yet know the true decompressed size).
"""
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_ARM, UC_PROT_READ, UC_PROT_WRITE, UC_PROT_EXEC, UcError
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_SP, UC_ARM_REG_LR

ROM_BASE = 0x08000000

# The codec's ARM-mode source bytes in the ROM (us version) -- copied to
# IWRAM 0x030028D4 at runtime; see docs/formats/text.md sec 6.
CODEC_ADDR = {"us": 0x08006108}
CODEC_LEN = 504

SCRATCH_BASE = 0x03000000
STACK_ADDR = 0x03000400
R2_SCRATCH_ADDR = 0x03000800  # &out_size -- confirmed: DecompressLzRle
# stores the decoded byte count here on return (`str r3,[r8,#0]`).
OUT_BUF_ADDR = 0x03010000
OUT_CAP = 0x4000  # 16KB; largest known real resource is 5120 bytes


def decode_lz_rle(rom: bytes, src_addr: int, codec_addr: int) -> bytes:
    mu = Uc(UC_ARCH_ARM, UC_MODE_ARM)
    mu.mem_map(ROM_BASE, 0x01000000, UC_PROT_READ | UC_PROT_EXEC)
    mu.mem_write(ROM_BASE, rom)
    mu.mem_map(SCRATCH_BASE, 0x1000, UC_PROT_READ | UC_PROT_WRITE)
    mu.mem_map(OUT_BUF_ADDR, OUT_CAP, UC_PROT_READ | UC_PROT_WRITE)

    mu.reg_write(UC_ARM_REG_R0, src_addr)
    mu.reg_write(UC_ARM_REG_R1, OUT_BUF_ADDR)
    mu.reg_write(UC_ARM_REG_R2, R2_SCRATCH_ADDR)
    mu.reg_write(UC_ARM_REG_SP, STACK_ADDR)
    mu.reg_write(UC_ARM_REG_LR, 0x1)  # invalid return address -- faults
    # back out of emu_start once the codec returns, caught below.
    try:
        mu.emu_start(codec_addr, 0, count=50_000_000)
    except UcError:
        pass

    return bytes(mu.mem_read(OUT_BUF_ADDR, OUT_CAP))


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    ver, addr_s = sys.argv[1], sys.argv[2]
    if ver not in CODEC_ADDR:
        sys.exit(f"codec address not yet confirmed for ver={ver!r}")
    addr = int(addr_s, 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    out = decode_lz_rle(rom, addr, CODEC_ADDR[ver])
    sys.stdout.buffer.write(out)


if __name__ == "__main__":
    main()
