#!/usr/bin/env python3
"""Decode a GBA BIOS-compressed resource blob (LZ77UnComp, HuffUnComp, or
RLUnComp) directly from a ROM address, matching the well-documented public
BIOS compression formats (GBATEK) that the game's generic resource
dispatcher (sub_0801DD90/sub_0801DE5C, see docs/formats/text.md sec 6 and
docs/formats/graphics.md) calls via svc 0x11/0x13/0x14 for types 1/2/3.

Unlike tools/graphics/decode_type6.py (a proprietary, undocumented codec that had to
be reverse-engineered), these are standard formats -- reimplemented
directly from the public spec, not by executing ROM code.

Verified against a real, live-confirmed example: ROM 0x080BCDD8, an
RLUnComp-compressed 32-byte (one 4bpp tile) sprite graphic, caught via an
mGBA watchpoint on OBJ tile VRAM (0x06010000) during actual gameplay --
see docs/formats/graphics.md's "A real, confirmed sprite tile" section.

Only rl_uncomp (type 3) has been exercised against a real, confirmed
resource so far. lz77_uncomp and huff_uncomp (types 1/2) are straight
reimplementations of the public GBA BIOS spec, not speculative, but no
resource found in this ROM has needed them yet -- treat them as
unverified-in-practice until one does.

Usage: decode_bios.py <ver> <hex addr>
  <hex addr> is the ROM address of the resource's 4-byte BIOS header
  (byte0 high nibble = type 1/2/3, low 3 bytes = decompressed size).
Writes raw decoded bytes to stdout.
"""
import struct
import sys

ROM_BASE = 0x08000000


def lz77_uncomp(rom: bytes, addr: int) -> bytes:
    off = addr - ROM_BASE
    size = rom[off + 1] | (rom[off + 2] << 8) | (rom[off + 3] << 16)
    pos = off + 4
    out = bytearray()
    while len(out) < size:
        flags = rom[pos]
        pos += 1
        for bit in range(8):
            if len(out) >= size:
                break
            if flags & (0x80 >> bit):
                b0, b1 = rom[pos], rom[pos + 1]
                pos += 2
                length = (b0 >> 4) + 3
                disp = (((b0 & 0xF) << 8) | b1) + 1
                start = len(out) - disp
                for k in range(length):
                    out.append(out[start + k])
            else:
                out.append(rom[pos])
                pos += 1
    return bytes(out[:size])


def rl_uncomp(rom: bytes, addr: int) -> bytes:
    """Stops exactly at the declared size, even mid-token -- matches real
    BIOS behavior (confirmed against the live-traced 0x080BCDD8 example;
    an earlier draft that consumed whole tokens regardless of `size`
    computed the wrong stream length)."""
    off = addr - ROM_BASE
    size = rom[off + 1] | (rom[off + 2] << 8) | (rom[off + 3] << 16)
    pos = off + 4
    out = bytearray()
    while len(out) < size:
        flag = rom[pos]
        pos += 1
        if flag & 0x80:
            length = (flag & 0x7F) + 3
            val = rom[pos]
            pos += 1
            take = min(length, size - len(out))
            out.extend([val] * take)
        else:
            length = (flag & 0x7F) + 1
            take = min(length, size - len(out))
            out.extend(rom[pos:pos + take])
            pos += take
    return bytes(out)


def huff_uncomp(rom: bytes, addr: int) -> bytes:
    off = addr - ROM_BASE
    header = rom[off]
    data_size_bits = header & 0x0F
    size = rom[off + 1] | (rom[off + 2] << 8) | (rom[off + 3] << 16)
    tree_pos = off + 4
    tree_size_byte = rom[tree_pos]
    tree_bytes = (tree_size_byte + 1) * 2
    bitstream_start = tree_pos + tree_bytes
    root = tree_pos

    word_pos = bitstream_start
    cur_word = 0
    bits_left = 0

    def get_bit():
        nonlocal word_pos, cur_word, bits_left
        if bits_left == 0:
            cur_word = struct.unpack_from("<I", rom, word_pos)[0]
            word_pos += 4
            bits_left = 32
        bits_left -= 1
        return (cur_word >> bits_left) & 1

    out = bytearray()
    while len(out) < size:
        value = 0
        shifts = 8 // data_size_bits
        for s in range(shifts):
            node_addr = root
            node = rom[node_addr]
            while True:
                bit = get_bit()
                offset = node & 0x3F
                end_flag = (node & 0x40) if bit else (node & 0x80)
                child_base = (node_addr & ~1) + offset * 2 + 2
                child_addr = child_base + (1 if bit else 0)
                if end_flag:
                    sym = rom[child_addr]
                    break
                node_addr = child_addr
                node = rom[node_addr]
            value |= (sym & ((1 << data_size_bits) - 1)) << (s * data_size_bits)
        out.append(value & 0xFF)
    return bytes(out[:size])


DECODERS = {1: lz77_uncomp, 2: huff_uncomp, 3: rl_uncomp}


def decode_bios(rom: bytes, addr: int) -> bytes:
    off = addr - ROM_BASE
    type_nibble = rom[off] >> 4
    decoder = DECODERS.get(type_nibble)
    if decoder is None:
        raise ValueError(f"not a BIOS-compressed header (type nibble {type_nibble:#x} at {addr:#010x})")
    return decoder(rom, addr)


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    ver, addr_s = sys.argv[1], sys.argv[2]
    addr = int(addr_s, 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    out = decode_bios(rom, addr)
    sys.stdout.buffer.write(out)


if __name__ == "__main__":
    main()
