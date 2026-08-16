#!/usr/bin/env python3
"""Pack data/monsters/monsters.json (curated, editable monster-stat JSON,
see tools/monsters/monster_migrate.py) into per-version, byte-exact
assembly for regions.<ver>.txt's monster-table row. See
docs/formats/folio_bruti.md.

Mirrors tools/text/pack_text.py's role for dialog text. Writes to
build/<ver>/monsters/ -- gitignored, like the rest of build/.
data/monsters/ itself is never touched by this script.

Usage: pack_monsters.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from monster_codec import RECORD_SIZE, pack_record


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def parse_monster_table_row(ver: str):
    """Returns (start, end, json_path, name), or None if not present yet."""
    row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] != "monster-table":
                continue
            if len(parts) != 5:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'monster-table <start> <end> <json> <name>'")
            if row is not None:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate monster-table row")
            _, start_s, end_s, json_path, name = parts
            row = (int(start_s, 16), int(end_s, 16), json_path, name)
    return row


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    row = parse_monster_table_row(ver)
    if row is None:
        print(f"no monster-table row in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    start_addr, end_addr, json_path, name = row

    records = json.loads(Path(json_path).read_text())

    lines: list[str] = [f"{name}:"]
    cursor = start_addr
    for record in records:
        cursor += emit_bytes(lines, pack_record(record))

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X} "
                  f"({len(records)} records * {RECORD_SIZE} bytes)")

    out_dir = Path(f"build/{ver}/monsters")
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / f"{name}.s").write_text("\n".join(lines) + "\n")
    print(f"packed {len(records)} monster records for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
