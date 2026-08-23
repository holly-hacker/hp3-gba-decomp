#!/usr/bin/env python3
"""Pack data/scripts/ (curated, editable object-script text, see
extract_objscript.py) into per-version, byte-exact assembly for
regions.<ver>.txt's objscript-table row. See docs/formats/object_script.md.

Mirrors tools/monsters/pack_monsters.py's role for the Folio Bruti table.
Effect id order comes from data/scripts/index.json (a JSON array of
filenames, position = effect id) -- NOT from sorting the directory
listing or parsing filenames -- so a script's file can be renamed freely
(see extract_objscript.py) without silently reordering the packed
g_apEffectScripts table. The pointer table itself is not stored on disk
at all -- it's fully determined by script order/size, so it's computed
and emitted here.

Writes to build/<ver>/objscript/ -- gitignored, like the rest of build/.
data/scripts/ itself is never touched by this script.

Usage: pack_objscript.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from objscript_codec import NAME_RE, SCRIPT_COUNT, encode_script, parse_script_text


def emit_bytes(lines: list[str], data: bytes) -> int:
    if not data:
        return 0
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def emit_pad_to_align4(lines: list[str], cursor: int) -> int:
    pad = (-cursor) % 4
    if pad:
        lines.append(".byte " + ", ".join(["0"] * pad))
    return pad


def parse_objscript_table_row(ver: str):
    """Returns (start, end, dir_path, name), or None if not present yet."""
    row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] != "objscript-table":
                continue
            if len(parts) != 5:
                sys.exit(f"regions.{ver}.txt:{lineno}: expected 'objscript-table <start> <end> <dir> <name>'")
            if row is not None:
                sys.exit(f"regions.{ver}.txt:{lineno}: duplicate objscript-table row")
            _, start_s, end_s, dir_path, name = parts
            row = (int(start_s, 16), int(end_s, 16), dir_path, name)
    return row


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    row = parse_objscript_table_row(ver)
    if row is None:
        print(f"no objscript-table row in regions.{ver}.txt -- nothing to pack", file=sys.stderr)
        return
    start_addr, end_addr, dir_path, name = row

    scripts_dir = Path(dir_path)
    index_path = scripts_dir / "index.json"
    filenames = json.loads(index_path.read_text())
    if len(filenames) != SCRIPT_COUNT:
        sys.exit(f"{index_path}: expected {SCRIPT_COUNT} entries, found {len(filenames)}")

    lines: list[str] = []
    cursor = start_addr
    script_labels = []
    for effect_id, filename in enumerate(filenames):
        label = Path(filename).stem
        if not NAME_RE.match(label):
            sys.exit(f"{index_path}: entry {effect_id} ({filename!r}) -- {label!r} isn't a valid "
                      "assembly label (letters/digits/underscore, not starting with a digit)")
        if label in script_labels:
            sys.exit(f"{index_path}: duplicate label {label!r} (entries {script_labels.index(label)} and {effect_id})")
        script_labels.append(label)
        instructions = parse_script_text((scripts_dir / filename).read_text())
        raw = encode_script(instructions)
        lines.append(f"{label}:")
        cursor += emit_bytes(lines, raw)

    cursor += emit_pad_to_align4(lines, cursor)
    lines.append(f"{name}:")
    for label in script_labels:
        lines.append(f".4byte {label}")
    cursor += 4 * SCRIPT_COUNT

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, regions file declares end 0x{end_addr:X}")

    out_dir = Path(f"build/{ver}/objscript")
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / f"{name}.s").write_text("\n".join(lines) + "\n")
    print(f"packed {len(filenames)} object scripts for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
