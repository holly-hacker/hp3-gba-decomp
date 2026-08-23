#!/usr/bin/env python3
"""Pack data/images/items/*.bin (curated, extracted-verbatim item icon
data, see tools/items/extract_item_icons.py) into byte-exact assembly
for regions.<ver>.txt's `item-icon-data` row. See
docs/formats/graphics.md's "Item icons" section.

Unlike tools/items/pack_items.py, this is a literal copy-through, not a
re-encode: no known encoder exists for the type-4 codec these icons
use, so data/images/items/<Name>.{palette,tiles,frames}.bin are exactly
the original ROM bytes, and packing just emits them back with labels
(gItemIcon<Name>Palette/Tiles/Frames) that pack_items.py's `.word`
references resolve against.

Writes to build/<ver>/items/ -- gitignored, like the rest of build/.
data/images/items/ itself is never touched by this script.

Usage: pack_item_icons.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from item_codec import icon_bin_paths, icon_labels


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

    items = json.loads(Path("data/items/items.json").read_text())
    icon_paths = [item["sIconPath"] for item in items if item.get("sIconPath") is not None]

    lines: list[str] = []
    cursor = start_addr
    count = 0
    for icon_path in icon_paths:
        palette_label, tiles_label, frames_label = icon_labels(icon_path)
        palette_bin, tiles_bin, frames_bin = icon_bin_paths(source_dir, icon_path)

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
