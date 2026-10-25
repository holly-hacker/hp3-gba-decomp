#!/usr/bin/env python3
"""Pack data/text/ (curated, editable dialog-string JSON, see
tools/text/extract_text.py) into per-version, byte-exact
assembly for regions.<ver>.txt's dialog-text/dialog-text-table rows. The
tree and symbol paths are reconstructed from the strings during packing;
each JSON file is a string array. See
docs/formats/text.md.

Mirrors tools/krawall/pack_krawall.py's role for audio: emits real .s text with
real labels (so the language pointer table resolves through the normal
assembler/linker), byte-exact against the real ROM (see
docs/formats/text.md). Each language blob starts word-aligned and
is zero-padded to a word, which is the real ROM layout.

Writes to build/<ver>/text/ -- gitignored, like the rest of build/.
data/text/ itself is never touched by this script.

Usage: pack_text.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent.parent))
from manifest import read_rows  # noqa: E402
from text_codec import (
    RAW_LANGS, VERSION_LANGS, build_blob, build_tree_from_strings,
    editable_to_bytes,
)


def emit_bytes(lines: list[str], data: bytes) -> None:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))


def emit_pad_to_align4(lines: list[str]) -> None:
    """Zero-pads to a word; each region starts word-aligned."""
    lines.append(".balign 4, 0")


def parse_text_rows(ver: str):
    langs = VERSION_LANGS[ver]
    """Returns (lang_rows, table_name). lang_rows: {lang_code: (json_path, name)}."""
    lang_rows: dict[str, tuple[str, str]] = {}
    table_name = None
    for lineno, parts in read_rows(f"regions.{ver}.txt"):
        if parts[0] == "dialog-text":
            if len(parts) != 3:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'dialog-text <json> <name>'")
            json_path, name = parts[1], parts[2]
            lang = Path(json_path).stem
            if lang not in langs:
                sys.exit(f"regions.{ver}.txt:{lineno}: {json_path} doesn't match a known language code {langs}")
            if lang in lang_rows:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate dialog-text row for language {lang!r}")
            lang_rows[lang] = (json_path, name)
        elif parts[0] == "dialog-text-table":
            if len(parts) != 2:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'dialog-text-table <name>'")
            if table_name is not None:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate dialog-text-table row")
            table_name = parts[1]
    if not lang_rows and table_name is None:
        # Not an error: this manifest has no dialog-text rows.
        return lang_rows, table_name
    missing = [l for l in langs if l not in lang_rows]
    if missing:
        sys.exit(f"regions.{ver}.txt: missing dialog-text rows for languages {missing}")
    if table_name is None:
        sys.exit(f"regions.{ver}.txt: no dialog-text-table row found")
    return lang_rows, table_name


def pack_language(lang: str, json_path: str, name: str) -> str:
    payload = json.loads(Path(json_path).read_text())
    if not isinstance(payload, list) or not all(isinstance(s, str) for s in payload):
        sys.exit(f"{json_path}: expected an array of strings")
    raw = lang in RAW_LANGS
    strings = [editable_to_bytes(s, raw) + b"\x00" for s in payload]
    tree, encode_map = build_tree_from_strings(strings)
    blob = build_blob(tree, strings, encode_map)

    lines: list[str] = [".balign 4", f"{name}:"]
    emit_bytes(lines, blob)
    emit_pad_to_align4(lines)

    return "\n".join(lines) + "\n"


def pack_table(ver: str, name: str, lang_rows: dict[str, tuple[str, str]]) -> str:
    lines = [".balign 4", f"{name}:"]
    for lang in VERSION_LANGS[ver]:
        _, lang_name = lang_rows[lang]
        lines.append(f".word {lang_name}")
    return "\n".join(lines) + "\n"


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    lang_rows, table_name = parse_text_rows(ver)
    if not lang_rows:
        print(f"no dialog-text rows in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    out_dir = Path(f"build/{ver}/text")
    out_dir.mkdir(parents=True, exist_ok=True)

    for lang, (json_path, name) in lang_rows.items():
        asm = pack_language(lang, json_path, name)
        (out_dir / f"{name}.s").write_text(asm)

    table_asm = pack_table(ver, table_name, lang_rows)
    (out_dir / f"{table_name}.s").write_text(table_asm)

    print(f"packed {len(lang_rows)} language string tables + pointer table for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
