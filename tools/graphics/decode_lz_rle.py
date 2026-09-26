#!/usr/bin/env python3
"""Decode a DecompressLzRle stream from a ROM address.

The source address is exactly the codec's input pointer: for type-7
resources it follows the four-byte resource header. See
docs/formats/graphics.md, "The DecompressLzRle codec, decoded".

Usage: decode_lz_rle.py <ver> <hex addr> (writes decoded bytes to stdout)
"""
import sys

ROM_BASE = 0x08000000


def decode_lz_rle(rom: bytes, src_addr: int) -> bytes:
    pos = src_addr - ROM_BASE
    output = bytearray()
    while True:
        control = rom[pos]
        pos += 1
        if control == 0:
            return bytes(output)
        if control & 0x80:
            second = rom[pos]
            pos += 1
            distance = ((control & 0x7F) << 3) | (second >> 5)
            length_code = second & 0x1F
            if length_code == 0:
                length = distance + 0x42
                fill = rom[pos]
                pos += 1
                output.extend(bytes((fill,)) * length)
            else:
                length = length_code + 2
                if not 0 < distance <= len(output):
                    raise ValueError(f"invalid LZ/RLE distance {distance} at {src_addr:#x}")
                for _ in range(length):
                    output.append(output[-distance])
        elif control & 0x40:
            length = (control & 0x3F) + 3
            fill = rom[pos]
            pos += 1
            output.extend(bytes((fill,)) * length)
        else:
            output.extend(rom[pos:pos + control])
            pos += control


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    ver, addr_s = sys.argv[1], sys.argv[2]
    addr = int(addr_s, 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    sys.stdout.buffer.write(decode_lz_rle(rom, addr))


if __name__ == "__main__":
    main()
