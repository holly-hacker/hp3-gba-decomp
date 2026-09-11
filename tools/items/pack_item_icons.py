#!/usr/bin/env python3
"""Pack data/images/items/*.bin (curated, extracted-verbatim item icon
data, see tools/items/extract_item_icons.py) into byte-exact assembly
for regions.<ver>.txt's `item-icon-data` row. See
docs/formats/graphics.md's "Item icons" section.

Unlike a JSON-driven pack step, this is a literal copy-through: no
known encoder exists for the type-4 codec these icons use, so
data/images/items/<Name>.{palette,tiles,frames}.bin are exactly the
original ROM bytes, and packing just emits them back with labels
(gItemIcon<Name>Palette/Tiles/Frames) that src/data/items.c's `extern`
declarations resolve against.

The real items' names/order (needed to derive each one's icon_slug())
are re-decoded directly from baserom.us.gba, the same way
extract_item_icons.py does -- not read from src/data/items.c, so this
script has no C-parsing dependency.

Writes to build/<ver>/items/ -- gitignored, like the rest of build/.
data/images/items/ itself is never touched by this script.

Usage: pack_item_icons.py <ver>
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from item_codec import ITEM_TABLE_ADDR, REAL_ITEM_COUNT, RECORD_SIZE, icon_bin_paths, icon_labels, icon_slug, unpack_record

sys.path.insert(0, str(Path(__file__).parent.parent / "text"))
from decode_dialog_text import decode_dialog_text

ROM_BASE = 0x08000000


def decode_name(rom: bytes, string_id: int) -> str:
    data = decode_dialog_text(rom, 0, string_id).rstrip(b"\x00")  # lang 0 = English US
    return data.decode("latin-1")


def real_item_icon_slugs() -> list[str]:
    """The 79 real items' icon_slug()s, in table order -- re-derived from
    baserom.us.gba rather than stored anywhere, see module docstring."""
    with open("baserom.us.gba", "rb") as f:
        rom = f.read()
    base = ITEM_TABLE_ADDR - ROM_BASE
    slugs = []
    for i in range(REAL_ITEM_COUNT):
        off = base + i * RECORD_SIZE
        record = unpack_record(rom[off:off + RECORD_SIZE])
        slugs.append(icon_slug(decode_name(rom, record["nNameTextId"])))
    return slugs


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def parse_item_icon_data_row(ver: str):
    """Returns (start, end, source_dir, name), or None if not present yet."""
    row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] != "item-icon-data":
                continue
            if len(parts) != 5:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'item-icon-data <start> <end> <dir> <name>'")
            if row is not None:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate item-icon-data row")
            _, start_s, end_s, source_dir, name = parts
            row = (int(start_s, 16), int(end_s, 16), source_dir, name)
    return row


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    row = parse_item_icon_data_row(ver)
    if row is None:
        print(f"no item-icon-data row in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    start_addr, end_addr, source_dir, name = row

    slugs = real_item_icon_slugs()

    lines: list[str] = []
    cursor = start_addr
    count = 0
    for slug in slugs:
        palette_label, tiles_label, frames_label = icon_labels(slug)
        palette_bin, tiles_bin, frames_bin = icon_bin_paths(source_dir, slug)

        lines.append(f"{palette_label}:")
        cursor += emit_bytes(lines, palette_bin.read_bytes())
        lines.append(f"{tiles_label}:")
        cursor += emit_bytes(lines, tiles_bin.read_bytes())
        lines.append(f"{frames_label}:")
        cursor += emit_bytes(lines, frames_bin.read_bytes())
        count += 1

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X} ({count} icons)")

    out_dir = Path(f"build/{ver}/items")
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / f"{name}.s").write_text("\n".join(lines) + "\n")
    print(f"packed {count} item icons for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
