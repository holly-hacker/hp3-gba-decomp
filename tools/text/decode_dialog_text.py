#!/usr/bin/env python3
"""Decode a dialog/UI text string from the game's real string table --
reimplemented directly from the disassembly of sub_08024DC8 (the Huffman-
style bitstream decoder) and sub_08024EB8/sub_08042588 (table init and
per-language dispatch). See docs/formats/text.md's "The text engine,
found" section for the full derivation and how each address below was
confirmed.

Layout, all ROM addresses (US, not yet checked against JP):
  0x0806BD78: 8 x u32, one ROM pointer per language (order matches the
    8-language cart: English US, English UK, French, German, Spanish,
    Italian, Dutch, Danish -- not yet independently confirmed beyond the
    decoded content itself matching each language).
  Each language blob (call its base B):
    B + 0x00: u32 header -- offset from B to the per-string offset table.
    B + 0x04: Huffman tree node table (header-4 bytes), 4 bytes/node:
      u16 zero-bit child @ +0, u16 one-bit child @ +2. Child value <=0xFF
      is a decoded output byte (leaf); >0xFF is the next node index
      (internal), computed as tree_base + (child-0x100)*4.
    B + header: u32[] offset table, one entry per string ID, each an
      offset from B to that string's compressed bitstream.

Decoded output bytes are the game's own glyph codes, not ASCII: values
0x00-0xEF are single-byte glyphs (0x20-0x7E happen to line up with ASCII
for the Latin cases exercised so far); values 0xF0-0xFF start a two-byte
extended glyph code for accented/non-Latin characters (see
sub_08020714 in docs/formats/text.md). This tool prints values <=0xEF as
their raw byte (readable as ASCII/Latin-1-ish for English) and anything
else as an escaped \\xNN pair, since the extended charmap isn't decoded
yet -- see docs/formats/text.md for what is and isn't confirmed there.

Usage: decode_dialog_text.py <ver> <lang 0-7> <string id (int or hex)>
Writes the decoded raw bytes to stdout.
"""
import struct
import sys

ROM_BASE = 0x08000000
LANG_TABLE = 0x0806BD78


class Blob:
    def __init__(self, rom: bytes, base: int):
        self.rom = rom
        self.base = base
        self.header = self._u32(base)
        self.tree = base + 4
        self.offtab = base + self.header

    def _u32(self, addr: int) -> int:
        return struct.unpack_from("<I", self.rom, addr - ROM_BASE)[0]

    def _u16(self, addr: int) -> int:
        return struct.unpack_from("<H", self.rom, addr - ROM_BASE)[0]

    def _u8(self, addr: int) -> int:
        return self.rom[addr - ROM_BASE]

    def _node_child(self, idx: int, bit: int) -> int:
        addr = self.tree + idx * 4 - 1024
        return self._u16(addr + (2 if bit else 0))

    def decode(self, string_id: int, max_out: int = 4096) -> bytes:
        off = self._u32(self.offtab + string_id * 4)
        pos = self.base + off
        byte = self._u8(pos)
        pos += 1
        bitpos = 0
        out = bytearray()
        pending = False
        while True:
            node = 0x100
            while True:
                bit = (byte >> bitpos) & 1
                node = self._node_child(node, bit)
                bitpos += 1
                if bitpos == 8:
                    bitpos = 0
                    byte = self._u8(pos)
                    pos += 1
                if node <= 0xFF:
                    break
            out.append(node)
            if len(out) > max_out:
                raise ValueError("decoded output exceeded max_out without a terminator")
            if node > 0xEF:
                terminator = False
                pending = not pending
            else:
                terminator = not pending and node == 0
                pending = False
            if terminator:
                break
        return bytes(out)


def decode_dialog_text(rom: bytes, lang: int, string_id: int) -> bytes:
    base = struct.unpack_from("<I", rom, LANG_TABLE + lang * 4 - ROM_BASE)[0]
    return Blob(rom, base).decode(string_id)


def main() -> None:
    if len(sys.argv) != 4:
        sys.exit(f"usage: {sys.argv[0]} <ver> <lang 0-7> <string id>")
    ver, lang_s, id_s = sys.argv[1], sys.argv[2], sys.argv[3]
    lang = int(lang_s)
    string_id = int(id_s, 0)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    out = decode_dialog_text(rom, lang, string_id)
    sys.stdout.buffer.write(out)


if __name__ == "__main__":
    main()
