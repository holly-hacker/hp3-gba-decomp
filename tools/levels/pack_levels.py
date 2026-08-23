#!/usr/bin/env python3
"""Pack data/levels/*.json (curated, editable per-character level-up
stat JSON, see tools/levels/extract_levels.py) into per-version,
byte-exact assembly for regions.<ver>.txt's level-table rows. See
docs/memory-map/battle.md.

Mirrors tools/monsters/pack_monsters.py's role for the Folio Bruti
table. Writes to build/<ver>/levels/ -- gitignored, like the rest of
build/. data/levels/ itself is never touched by this script.

Usage: pack_levels.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from level_codec import RECORD_SIZE, pack_record


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def parse_level_table_rows(ver: str):
    """Returns a list of (start, end, json_path, name) rows."""
    rows = []
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] != "level-table":
                continue
            if len(parts) != 5:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'level-table <start> <end> <json> <name>'")
            _, start_s, end_s, json_path, name = parts
            rows.append((int(start_s, 16), int(end_s, 16), json_path, name))
    return rows


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    rows = parse_level_table_rows(ver)
    if not rows:
        print(f"no level-table rows in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return

    out_dir = Path(f"build/{ver}/levels")
    out_dir.mkdir(parents=True, exist_ok=True)

    total = 0
    for start_addr, end_addr, json_path, name in rows:
        records = json.loads(Path(json_path).read_text())

        lines: list[str] = [f"{name}:"]
        cursor = start_addr
        for record in records:
            cursor += emit_bytes(lines, pack_record(record))

        if cursor != end_addr:
            sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                      f"regions file declares end 0x{end_addr:X} "
                      f"({len(records)} records * {RECORD_SIZE} bytes)")

        (out_dir / f"{name}.s").write_text("\n".join(lines) + "\n")
        total += len(records)

    print(f"packed {total} level records ({len(rows)} tables) for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
