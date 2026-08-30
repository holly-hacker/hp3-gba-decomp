#!/usr/bin/env python3
"""Decode BG character tiles via BgTileCodec_candidate (0x08006300),
executed via Unicorn against the real ARM-mode ROM bytes, same approach
as decode_type6.py/decode_type4.py. See docs/formats/graphics.md's
"On-demand per-tile BG streaming" section.

Calling convention, captured live via an mGBA breakpoint on the codec's
IWRAM entry (0x030033CC):
  r0 = a per-tile packed value from a dwBgTilesetA/B offset table
       (real_addr = 0x08000000 + (r0 >> 3) is the tile's compressed data)
  r1 = VRAM destination (redirected to a scratch buffer here)
  r2 = 0x20 (fixed -- one 4bpp 8x8 tile)
  r3 = pointer to a 292-byte context table, a verbatim copy of the first
       0x124 bytes at the tileset resource's blob_base
       (resource_ptr + size_field + 8) -- a symbol/frequency table for
       the codec, not pixel data.

BgTileDecoder maps the ROM into Unicorn once and reuses that instance
across many tile decodes -- re-mapping and re-writing the ~16MB ROM
image per tile (the original, naive approach) made whole-room extraction
extremely slow for no benefit, since only registers and the tiny context
table actually change between tiles.
"""
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_ARM, UC_PROT_READ, UC_PROT_WRITE, UC_PROT_EXEC, UcError
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3, UC_ARM_REG_SP, UC_ARM_REG_LR

ROM_BASE = 0x08000000
CODEC_ADDR = {"us": 0x08006300}

IWRAM_BASE = 0x03000000
IWRAM_SIZE = 0x00008000  # 32KB real GBA IWRAM
CONTEXT_ADDR = 0x03005650  # real address the game itself uses
STACK_ADDR = 0x03007F00
OUT_BUF_ADDR = 0x06000000  # real BG VRAM address, mapped RW here
OUT_CAP = 0x20


class BgTileDecoder:
    """Reusable Unicorn instance: map the ROM once, decode many tiles."""

    def __init__(self, rom: bytes, codec_addr: int):
        self.codec_addr = codec_addr
        self.mu = mu = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        mu.mem_map(ROM_BASE, 0x01000000, UC_PROT_READ | UC_PROT_EXEC)
        mu.mem_write(ROM_BASE, rom)
        mu.mem_map(IWRAM_BASE, IWRAM_SIZE, UC_PROT_READ | UC_PROT_WRITE)
        mu.mem_map(OUT_BUF_ADDR, 0x1000, UC_PROT_READ | UC_PROT_WRITE)
        self._last_context = None

    def decode(self, r0_value: int, context_bytes: bytes) -> bytes:
        mu = self.mu
        if context_bytes != self._last_context:
            mu.mem_write(CONTEXT_ADDR, context_bytes)
            self._last_context = context_bytes
        mu.mem_write(OUT_BUF_ADDR, b"\x00" * OUT_CAP)  # clear stale output

        mu.reg_write(UC_ARM_REG_R0, r0_value)
        mu.reg_write(UC_ARM_REG_R1, OUT_BUF_ADDR)
        mu.reg_write(UC_ARM_REG_R2, OUT_CAP)
        mu.reg_write(UC_ARM_REG_R3, CONTEXT_ADDR)
        mu.reg_write(UC_ARM_REG_SP, STACK_ADDR)
        mu.reg_write(UC_ARM_REG_LR, 0x1)  # invalid return address -- faults
        # back out of emu_start once the codec returns, caught below.
        try:
            mu.emu_start(self.codec_addr, 0, count=200_000)
        except UcError:
            pass

        return bytes(mu.mem_read(OUT_BUF_ADDR, OUT_CAP))


def build_tile_offsets(blob_base: int, offset_table_bytes: bytes, num_entries: int) -> list[int]:
    """Walks the decoded per-tile offset table (the gap-code stream
    right after dwBgTilesetA/B's 2-byte internal header) into a real
    per-tile r0 value for BgTileDecoder.decode(), one per tile index."""
    MASK = 0xFFFFFFFF
    val = (blob_base + (-0x7FFFEDC)) * 8 & MASK
    pos = 2  # skip 2-byte internal header
    offsets = []
    for _ in range(num_entries):
        offsets.append(val)
        b = offset_table_bytes[pos]
        if b == 0xFF:
            gap = (offset_table_bytes[pos + 1] << 8) + offset_table_bytes[pos + 2]
            pos += 3
        else:
            gap = 0x20 + b
            pos += 1
        val = (val + gap) & MASK
    return offsets


def main() -> None:
    sys.exit("no standalone CLI -- see dump_bg_tiles.py")


if __name__ == "__main__":
    main()
