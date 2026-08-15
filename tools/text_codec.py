#!/usr/bin/env python3
"""Codec for the game's dialog/UI text string tables -- reimplemented
directly from sub_08024DC8 (decode) and its blob layout
(sub_08024EB8/sub_08042588). See docs/formats/text.md's "The real dialog
string table, decoded" section for the full derivation.

Blob layout, per language, base address B (found via the 8-entry pointer
table at ROM 0x0806BD78):
    B + 0x00: u32 header -- byte offset from B to the offset table.
    B + 0x04: Huffman tree node table, `header - 4` bytes (4 bytes/node:
      u16 zero-bit child @ +0, u16 one-bit child @ +2). A child value
      <=0xFF is a decoded output byte (leaf); >0xFF is the next node's
      index, at tree_base + (child - 0x100) * 4.
    B + header: u32[] offset table, one entry per string ID (count N
      derived below), each a byte offset from B to that string's
      compressed bitstream.
    Compressed bitstreams follow immediately after the offset table, one
    per string in ID order, each starting at a fresh byte boundary (the
    previous string's trailing partial byte is padding, confirmed
    empirically: offset[id+1] - offset[id] == ceil(bits_used(id) / 8)
    for every ID checked).

String count N is derived, not scanned: since the bitstream section
starts immediately after the offset table with no gap, offset[0] ==
header + 4*N, so N = (offset[0] - header) // 4. Verified against
English (US, lang 0): gives exactly 2767, matching an 0xACF boundary
constant seen near a real sub_08020FF8 call site in the disassembly.

Bit order: LSB-first within each byte (bit 0 first), refilling one byte
at a time.

Decoded glyph bytes <=0xEF are single-byte codes; >0xEF starts a
two-byte extended code, combined as (byte0<<8)|byte1 -- see
docs/formats/text.md for what is and isn't decoded about the extended
charmap itself. This codec operates on the raw glyph-code byte stream,
not on any character mapping.
"""
import struct

ROM_BASE = 0x08000000
LANG_TABLE = 0x0806BD78
LANGS = ["en_us", "en_gb", "fr", "de", "es", "it", "nl", "da"]


def rd8(rom: bytes, addr: int) -> int:
    return rom[addr - ROM_BASE]


def rd16(rom: bytes, addr: int) -> int:
    return struct.unpack_from("<H", rom, addr - ROM_BASE)[0]


def rd32(rom: bytes, addr: int) -> int:
    return struct.unpack_from("<I", rom, addr - ROM_BASE)[0]


def lang_base(rom: bytes, lang_index: int) -> int:
    return rd32(rom, LANG_TABLE + lang_index * 4)


class TextBlob:
    """Wraps one language's blob, either read live from ROM bytes at
    `base`, or reconstructed from a captured tree (for encoding)."""

    def __init__(self, tree_bytes: bytes, offsets: list[int] | None = None):
        self.tree_bytes = tree_bytes
        self.header = 4 + len(tree_bytes)
        self.offsets = offsets  # only needed for decode-from-rom use

    @classmethod
    def from_rom(cls, rom: bytes, base: int) -> "TextBlob":
        header = rd32(rom, base)
        tree_len = header - 4
        tree_bytes = rom[base + 4 - ROM_BASE: base + 4 - ROM_BASE + tree_len]
        offtab_addr = base + header
        off0 = rd32(rom, offtab_addr)
        n = (off0 - header) // 4
        offsets = [rd32(rom, offtab_addr + i * 4) for i in range(n)]
        blob = cls(tree_bytes, offsets)
        blob.rom = rom
        blob.base = base
        return blob

    @property
    def count(self) -> int:
        return len(self.offsets)

    def _node_child(self, node: int, bit: int) -> int:
        idx = node - 0x100
        off = idx * 4 + (2 if bit else 0)
        return struct.unpack_from("<H", self.tree_bytes, off)[0]

    def _decode_impl(self, string_id: int, want_paths: bool):
        pos = self.base + self.offsets[string_id]
        byte = rd8(self.rom, pos)
        pos += 1
        bitpos = 0
        out = bytearray()
        paths: list[tuple[int, tuple[int, ...]]] = []
        pending = False
        while True:
            node = 0x100
            path: list[int] = []
            while True:
                bit = (byte >> bitpos) & 1
                if want_paths:
                    path.append(bit)
                node = self._node_child(node, bit)
                bitpos += 1
                if bitpos == 8:
                    bitpos = 0
                    byte = rd8(self.rom, pos)
                    pos += 1
                if node <= 0xFF:
                    break
            out.append(node)
            if want_paths:
                paths.append((node, tuple(path)))
            if node > 0xEF:
                terminator = False
                pending = not pending
            else:
                terminator = (not pending) and node == 0
                pending = False
            if terminator:
                break
        return (bytes(out), paths) if want_paths else bytes(out)

    def decode(self, string_id: int) -> bytes:
        return self._decode_impl(string_id, want_paths=False)

    def decode_with_paths(self, string_id: int) -> tuple[bytes, list[tuple[int, tuple[int, ...]]]]:
        """Like decode(), but also returns, per emitted symbol, the
        exact bit path taken through the tree -- needed to build an
        encode map, since the tree has structurally-reachable duplicate
        leaves (multiple paths can decode to the same byte value) that
        real content never actually exercises through more than one of
        them. See build_encode_map_from_corpus()."""
        return self._decode_impl(string_id, want_paths=True)

    def decode_all(self) -> dict[int, bytes]:
        return {i: self.decode(i) for i in range(self.count)}


def path_to_int(path: list[int]) -> int:
    """Packs a bit path into a single self-describing integer, via the
    standard leading-1-sentinel trick: value = (1 << len(path)) | code,
    with path[0] as the MSB (right after the sentinel bit). Max real
    depth is 11 bits (see docs/formats/text.md), so this always fits
    comfortably in a plain JSON integer/small int -- used so
    data/text/*.json stores one compact number per symbol instead of a
    nested array of 0/1s."""
    value = 1
    for bit in path:
        value = (value << 1) | bit
    return value


def int_to_path(value: int) -> list[int]:
    """Inverse of path_to_int()."""
    length = value.bit_length() - 1
    return [(value >> (length - 1 - i)) & 1 for i in range(length)]


def build_encode_map_from_corpus(blob: "TextBlob") -> dict[int, list[int]]:
    """Builds {byte_value: [bit, bit, ...]} empirically, from the actual
    bit paths real strings in this blob use -- NOT a structural DFS over
    the tree. The tree contains structurally-reachable duplicate leaves
    (the same byte value reachable via more than one path), verified
    (this session) to never actually be exercised more than one way by
    real content (zero path conflicts across every string in every
    language). Using the tree structurally instead of empirically picks
    an arbitrary one of the duplicate paths, which breaks byte-exact
    re-encoding whenever it disagrees with the one the original data
    actually used -- this function avoids that by construction. Raises
    if a real conflict is ever found (would mean this blob's content
    doesn't fit the "each symbol has one real path" property verified
    for the shipped ROM)."""
    encode_map: dict[int, list[int]] = {}
    for sid in range(blob.count):
        _, paths = blob.decode_with_paths(sid)
        for sym, path in paths:
            path_list = list(path)
            if sym in encode_map and encode_map[sym] != path_list:
                raise ValueError(
                    f"symbol {sym:#x} has conflicting paths in real data: "
                    f"{encode_map[sym]} vs {path_list} (string id {sid})"
                )
            encode_map[sym] = path_list
    return encode_map


def encode_string(encode_map: dict[int, list[int]], data: bytes) -> bytes:
    """Encodes a glyph-code byte string, as produced by decode() --
    which already includes the trailing 0x00 terminator byte in its
    output, so `data` must too (do not append an extra one here)."""
    bits: list[int] = []
    for b in data:
        bits.extend(encode_map[b])
    out = bytearray()
    cur = 0
    nbits = 0
    for bit in bits:
        cur |= bit << nbits
        nbits += 1
        if nbits == 8:
            out.append(cur)
            cur = 0
            nbits = 0
    if nbits:
        out.append(cur)
    return bytes(out)


# Real character assignments for glyph codes outside the plain-ASCII
# passthrough range (0x20-0x7A), decoded this session by cross-reading
# every real string containing them across all 8 languages (proper
# nouns shared verbatim in the credits -- "Hernández", "Gómez",
# "Börjel" -- pin several codes at once; French/Spanish/Italian
# grammar pins the rest). See docs/formats/text.md's "The extended
# charmap, decoded" section for the full derivation and evidence.
#
# 0x7B/0x7C/0x7D/0x7E are printable ASCII positions that turn out to be
# REPURPOSED, not literal '{', '|', '}', '~' -- confirmed by real
# content: '{' only ever appears in the fixed legal-disclaimer string,
# in "trademarks of and { Warner Bros." (-> (c) Warner Bros.); '}'/'~'
# appear only in Spanish, at Spanish-specific inverted punctuation
# positions ("}NO FUE UNA PESADILLA!" -> "!No fue..."[inverted !]);
# '|' appears only in French, in "d'|il" -> "d'oeil" (the "oe" ligature
# needed for "coup d'oeil", a glance).
#
# 0x83 upward line up, in relative order, with ISO-8859-1/Latin-1's own
# accented-letter ordering (a-grave, a-acute, a-circumflex, a-diaeresis,
# a-ring, ae, c-cedilla, e-grave, ...), just renumbered densely to only
# the letters these 6 non-English languages actually use -- strong
# structural corroboration for the whole table at once, not just each
# entry's own context.
CHARMAP: dict[int, str] = {
    0x0A: "\n",  # explicit line break within a dialog/text box
    0x7B: "©",  # (c) copyright
    0x7C: "œ",  # oe ligature (French, "coup d'oeil")
    0x7D: "¡",  # inverted exclamation mark (Spanish)
    0x7E: "¿",  # inverted question mark (Spanish)
    0x83: "Ä",  # A-diaeresis
    0x84: "Å",  # A-ring
    0x85: "Æ",  # AE ligature
    0x87: "È",  # E-grave
    0x88: "É",  # E-acute
    0x8C: "Ì",  # I-grave
    0x8D: "Í",  # I-acute
    0x95: "Ö",  # O-diaeresis
    0x96: "Ø",  # O-stroke
    0x98: "Ú",  # U-acute
    0x99: "Ü",  # U-diaeresis
    0x9A: "ß",  # sharp s (German)
    0x9B: "à",  # a-grave
    0x9C: "á",  # a-acute
    0x9D: "â",  # a-circumflex
    0x9F: "ä",  # a-diaeresis
    0xA0: "å",  # a-ring
    0xA1: "æ",  # ae ligature
    0xA2: "ç",  # c-cedilla
    0xA3: "è",  # e-grave
    0xA4: "é",  # e-acute
    0xA5: "ê",  # e-circumflex
    0xA6: "ë",  # e-diaeresis
    0xA7: "ì",  # i-grave
    0xA8: "í",  # i-acute
    0xA9: "î",  # i-circumflex
    0xAA: "ï",  # i-diaeresis
    0xAB: "ñ",  # n-tilde
    0xAC: "ò",  # o-grave
    0xAD: "ó",  # o-acute
    0xAE: "ô",  # o-circumflex
    0xB0: "ö",  # o-diaeresis
    0xB1: "ø",  # o-stroke
    0xB2: "ù",  # u-grave
    0xB3: "ú",  # u-acute
    0xB4: "û",  # u-circumflex
    0xB5: "ü",  # u-diaeresis
    0xB8: "…",  # ellipsis
    0xB9: "™",  # trademark (paired with "Challenge Everything"/"EA GAMES")
    0xBA: "Œ",  # OE ligature, capital
    0xBB: "®",  # registered trademark (paired with "Game Boy"/"Game Link")
    0xBC: " ",  # non-breaking space (French pre-punctuation spacing, etc.)
}
CHARMAP_REVERSE: dict[str, int] = {v: k for k, v in CHARMAP.items()}
assert len(CHARMAP_REVERSE) == len(CHARMAP), "CHARMAP has a duplicate character value"


def bytes_to_editable(data: bytes) -> str:
    """Reversible glyph-bytes -> human-editable string, for data/text/
    JSON. `data` must NOT include the trailing 0x00 terminator (strip it
    first -- decode() includes it, encode_string() expects it back).
    Plain-ASCII glyph codes (0x20-0x7A) round-trip as themselves. Codes
    with a real character identified this session (CHARMAP, above)
    round-trip as that real Unicode character. Anything still
    unresolved (control bytes, and the >0xEF two-byte extended codes --
    none of which any real string in this ROM actually uses, see
    docs/formats/text.md) falls back to a Unicode Private Use Area
    placeholder: single byte b -> U+E000+b; two-byte code (b0<<8)|b1
    (b0 in 0xF0-0xFF) -> that value directly, since it already falls in
    U+F000-U+FFFF."""
    out = []
    i = 0
    while i < len(data):
        b = data[i]
        if b in CHARMAP:
            out.append(CHARMAP[b])
            i += 1
        elif 0x20 <= b <= 0x7A:
            out.append(chr(b))
            i += 1
        elif b > 0xEF:
            combined = (b << 8) | data[i + 1]
            out.append(chr(combined))
            i += 2
        else:
            out.append(chr(0xE000 + b))
            i += 1
    return "".join(out)


def editable_to_bytes(s: str) -> bytes:
    """Inverse of bytes_to_editable(). Output does NOT include a
    trailing 0x00 -- append one before calling encode_string()."""
    out = bytearray()
    for ch in s:
        cp = ord(ch)
        if ch in CHARMAP_REVERSE:
            out.append(CHARMAP_REVERSE[ch])
        elif 0x20 <= cp <= 0x7A:
            out.append(cp)
        elif 0xE000 <= cp <= 0xE0FF:
            out.append(cp - 0xE000)
        elif 0xF000 <= cp <= 0xFFFF:
            out.append(cp >> 8)
            out.append(cp & 0xFF)
        else:
            raise ValueError(f"codepoint {cp:#x} not representable in the glyph charmap")
    return bytes(out)


def build_blob(tree_bytes: bytes, strings_in_id_order: list[bytes], encode_map: dict[int, list[int]]) -> bytes:
    """Reassembles a full language blob: header + tree + offset table +
    concatenated per-string bitstreams (byte-aligned each), matching the
    real ROM layout exactly when strings_in_id_order is unmodified from
    a real decode."""
    n = len(strings_in_id_order)
    header = 4 + len(tree_bytes)
    encoded = [encode_string(encode_map, s) for s in strings_in_id_order]
    offsets = []
    pos = header + 4 * n
    for enc in encoded:
        offsets.append(pos)
        pos += len(enc)
    out = bytearray()
    out += struct.pack("<I", header)
    out += tree_bytes
    for off in offsets:
        out += struct.pack("<I", off)
    for enc in encoded:
        out += enc
    return bytes(out)
