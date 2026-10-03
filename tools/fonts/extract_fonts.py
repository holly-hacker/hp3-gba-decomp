#!/usr/bin/env python3
"""Extract every fonts manifest row from the baserom as PNG glyph atlases.

Each row's range is walked font by font (a font's length follows from its
header) and must end exactly at the row's end address. Every font must rebuild
from its PNG to the ROM's bytes. See fonts.py and docs/formats/fonts.md.

data/fonts/ is gitignored, same footing as the baserom; extraction overwrites
local PNG edits.

Usage: extract_fonts.py <ver> [bank ...]
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import fonts
from pack_fonts import font_from_file, font_rows

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "graphic_blob"))
import blobs


def main() -> None:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        sys.exit(f"usage: {sys.argv[0]} <ver> [bank ...]")
    ver, wanted = args[0], args[1:]
    try:
        rom = Path(f"baserom.{ver}.gba").read_bytes()
        rows = [r for r in font_rows(ver) if not wanted or r[3] in wanted]
        for start, end, source, bank in rows:
            addr, found = start, []
            while addr < end:
                font, next_addr, raw = fonts.parse(rom, addr)
                found.append((font, raw))
                addr = next_addr
            if addr != end:
                raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
            source.mkdir(parents=True, exist_ok=True)
            for old in source.glob("*.png"):
                old.unlink()
            entries = []
            for i, (font, raw) in enumerate(found):
                entry = {"name": f"{bank.removesuffix('s')}{i:02d}", "first": font.first, "last": font.last,
                         "height": font.height, "widths": font.widths}
                if font.flags is not None:
                    entry["flags"] = "".join(map(str, font.flags))
                size, pixels = fonts.atlas(font)
                blobs.write_png(source / f"{entry['name']}.png", size, pixels, fonts.GRAY, [0])
                if fonts.build(font_from_file(source, entry)) != raw:
                    raise ValueError(f"{entry['name']}: rebuilding from the PNG gives different bytes")
                entries.append(entry)
            (source / "bank.json").write_text(
                '{\n "format": 1,\n "fonts": [\n' + ",\n".join("  " + json.dumps(e) for e in entries) + "\n ]\n}\n")
            print(f"{ver}: extracted {bank}: {len(entries)} fonts in {source}")
        if not rows:
            print(f"{ver}: no fonts regions")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
