#!/usr/bin/env python3
"""One-time bootstrap: decode the game's real dialog/UI string tables
from the US baserom into curated, editable JSON under data/text/. See
docs/formats/text.md's "The real dialog string table, decoded" section.

The string-only JSON files are local, gitignored editable source. Existing
files are kept unless --force is passed, so extract-all does not overwrite
local edits. Run extract-text once on a fresh checkout before building US.

Text is currently only located/decoded from the US/EU cart (8 languages
in one ROM image); the JP cart's dialog text has not been investigated
and is very likely a different mechanism entirely (JP needs far more than
256 base + 4096 extended glyph codes) -- this only ever reads
baserom.us.gba.

Each data/text/<lang>.json is an array with one entry per string ID
(index = ID), run through text_codec.bytes_to_editable(). Known glyphs
become readable characters; unknown control or extended codes become
reversible Private Use Area placeholders.

Usage: extract_text.py [--force]   (reads baserom.us.gba, writes data/text/)
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from text_codec import TextBlob, bytes_to_editable, lang_base, LANGS


def main() -> None:
    if len(sys.argv) > 2 or (len(sys.argv) == 2 and sys.argv[1] != "--force"):
        sys.exit(f"usage: {sys.argv[0]} [--force]")
    force = len(sys.argv) == 2
    with open("baserom.us.gba", "rb") as f:
        rom = f.read()

    out_dir = Path("data/text")
    out_dir.mkdir(parents=True, exist_ok=True)

    for i, code in enumerate(LANGS):
        path = out_dir / f"{code}.json"
        if path.exists() and not force:
            print(f"{code}: keeping existing {path}", file=sys.stderr)
            continue
        base = lang_base(rom, i)
        blob = TextBlob.from_rom(rom, base)
        strings = []
        for sid in range(blob.count):
            data = blob.decode(sid)
            assert data[-1] == 0, f"{code} string {sid}: missing terminator"
            strings.append(bytes_to_editable(data[:-1]))

        path.write_text(json.dumps(strings, indent=1, ensure_ascii=False) + "\n")
        print(f"{code}: {blob.count} strings -> {path}", file=sys.stderr)


if __name__ == "__main__":
    main()
