#!/usr/bin/env python3
"""Pack data/text/ (curated, editable dialog-string JSON, currently
US-only -- see tools/text/extract_text.py) into per-version, byte-exact
assembly for regions.<ver>.txt's dialog-text/dialog-text-table rows. The
tree and symbol paths are reconstructed from the strings during packing;
each JSON file is a string array. See
docs/formats/text.md.

Mirrors tools/krawall/pack_krawall.py's role for audio: emits real .s text with
real labels (so the language pointer table resolves through the normal
assembler/linker), byte-exact against the real ROM (see
docs/formats/text.md). Each language blob is padded to 4-byte
alignment to match the real ROM layout (verified: the padding is always
zero bytes, and its length is exactly what closes the gap to the next
language's real base address).

Writes to build/<ver>/text/ -- gitignored, like the rest of build/.
data/text/ itself is never touched by this script.

Usage: pack_text.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from text_codec import (
    LANGS, build_blob, build_tree_from_strings, editable_to_bytes,
)


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def emit_pad_to_align4(lines: list[str], cursor: int) -> int:
    pad = (-cursor) % 4
    if pad:
        lines.append(".byte " + ", ".join(["0"] * pad))
    return pad


def parse_text_rows(ver: str):
    """Returns (lang_rows, table_row). lang_rows: {lang_code: (start, end, json_path, name)}.
    table_row: (start, end, name)."""
    lang_rows: dict[str, tuple[int, int, str, str]] = {}
    table_row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] == "dialog-text":
                if len(parts) != 5:
                    sys.exit(f"regions.{ver}.txt:{lineno}: expected 'dialog-text <start> <end> <json> <name>'")
                _, start, end, json_path, name = parts
                lang = Path(json_path).stem
                if lang not in LANGS:
                    sys.exit(f"regions.{ver}.txt:{lineno}: {json_path} doesn't match a known language code {LANGS}")
                if lang in lang_rows:
                    sys.exit(f"regions.{ver}.txt:{lineno}: duplicate dialog-text row for language {lang!r}")
                lang_rows[lang] = (int(start, 16), int(end, 16), json_path, name)
            elif parts[0] == "dialog-text-table":
                if len(parts) != 4:
                    sys.exit(f"regions.{ver}.txt:{lineno}: expected 'dialog-text-table <start> <end> <name>'")
                if table_row is not None:
                    sys.exit(f"regions.{ver}.txt:{lineno}: duplicate dialog-text-table row")
                _, start, end, name = parts
                table_row = (int(start, 16), int(end, 16), name)
    if not lang_rows and table_row is None:
        # Not an error: dialog text hasn't been located/extracted for
        # this ROM version yet (e.g. JP -- see docs/formats/text.md).
        return lang_rows, table_row
    missing = [l for l in LANGS if l not in lang_rows]
    if missing:
        sys.exit(f"regions.{ver}.txt: missing dialog-text rows for languages {missing}")
    if table_row is None:
        sys.exit(f"regions.{ver}.txt: no dialog-text-table row found")
    return lang_rows, table_row


def pack_language(lang: str, start_addr: int, end_addr: int, json_path: str, name: str) -> str:
    payload = json.loads(Path(json_path).read_text())
    if not isinstance(payload, list) or not all(isinstance(s, str) for s in payload):
        sys.exit(f"{json_path}: expected an array of strings")
    strings = [editable_to_bytes(s) + b"\x00" for s in payload]
    tree, encode_map = build_tree_from_strings(strings)
    blob = build_blob(tree, strings, encode_map)

    lines: list[str] = [f"{name}:"]
    cursor = start_addr
    cursor += emit_bytes(lines, blob)
    cursor += emit_pad_to_align4(lines, cursor)

    if cursor != end_addr:
        sys.exit(f"{name} ({lang}): packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X}")

    return "\n".join(lines) + "\n"


def pack_table(start_addr: int, end_addr: int, name: str, lang_rows: dict[str, tuple[int, int, str, str]]) -> str:
    lines = [f"{name}:"]
    cursor = start_addr
    for lang in LANGS:
        _, _, _, lang_name = lang_rows[lang]
        lines.append(f".word {lang_name}")
        cursor += 4
    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X}")
    return "\n".join(lines) + "\n"


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    lang_rows, table_row = parse_text_rows(ver)
    if not lang_rows:
        print(f"no dialog-text rows in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    t_start, t_end, t_name = table_row
    out_dir = Path(f"build/{ver}/text")
    out_dir.mkdir(parents=True, exist_ok=True)

    for lang, (start, end, json_path, name) in lang_rows.items():
        asm = pack_language(lang, start, end, json_path, name)
        (out_dir / f"{name}.s").write_text(asm)

    table_asm = pack_table(t_start, t_end, t_name, lang_rows)
    (out_dir / f"{t_name}.s").write_text(table_asm)

    print(f"packed {len(lang_rows)} language string tables + pointer table for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
