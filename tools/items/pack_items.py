#!/usr/bin/env python3
"""Pack data/items/items.json (curated, editable item/equipment
table JSON, see tools/items/extract_items.py) into per-version,
byte-exact assembly for regions.<ver>.txt's item-table row. See
docs/formats/save.md's "Item quantities and equipment" section.

Mirrors tools/monsters/pack_monsters.py's role for the Folio Bruti
monster table. Writes to build/<ver>/items/ -- gitignored, like the
rest of build/. data/items/ itself is never touched by this script.

Usage: pack_items.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from item_codec import RECORD_SIZE, icon_labels, pack_head, pack_icons_literal, pack_tail


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def emit_record(lines: list[str], record: dict) -> int:
    """Emit one 52-byte record: literal bytes for every field except the
    3 icon pointers, which for a real item (sIconPath set) become `.word`
    references to regions.<ver>.txt's `label` rows instead of literal
    addresses -- see item_codec module docstring."""
    size = emit_bytes(lines, pack_head(record))
    icon_path = record.get("sIconPath")
    if icon_path is not None:
        for label in icon_labels(icon_path):
            lines.append(f".word {label}")
        size += 12
    else:
        size += emit_bytes(lines, pack_icons_literal(record))
    size += emit_bytes(lines, pack_tail(record))
    return size


def parse_item_table_row(ver: str):
    """Returns (start, end, json_path, name), or None if not present yet."""
    row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] != "item-table":
                continue
            if len(parts) != 5:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'item-table <start> <end> <json> <name>'")
            if row is not None:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate item-table row")
            _, start_s, end_s, json_path, name = parts
            row = (int(start_s, 16), int(end_s, 16), json_path, name)
    return row


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    row = parse_item_table_row(ver)
    if row is None:
        print(f"no item-table row in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    start_addr, end_addr, json_path, name = row

    records = json.loads(Path(json_path).read_text())

    lines: list[str] = [f"{name}:"]
    cursor = start_addr
    for record in records:
        cursor += emit_record(lines, record)

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X} "
                  f"({len(records)} records * {RECORD_SIZE} bytes)")

    out_dir = Path(f"build/{ver}/items")
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / f"{name}.s").write_text("\n".join(lines) + "\n")
    print(f"packed {len(records)} item records for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
