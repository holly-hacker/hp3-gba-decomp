#!/usr/bin/env python3
"""Extract the US portrait image bank as ordered, original encoded bytes.

The 72-entry portrait table points to 54 unique resources. Each unique
resource consists of compressed tiles, frame data, and a 512-byte palette.
The table proves their order and boundaries; this script verifies that the
resources fill one contiguous ROM range before writing local source files.
PNG rendering remains available through extract_portraits.py.

Usage: extract_portrait_bank.py [--index-only]
"""
import json
import struct
import sys
from pathlib import Path

from extract_portraits import RECORD_COUNT, TABLE_BASE, extract_one

sys.path.insert(0, str(Path(__file__).parent.parent / "images"))
from pack_images import image_banks  # noqa: E402

ROM_BASE = 0x08000000
PALETTE_SIZE = 0x200
VER = "us"


def records(rom: bytes, bank_start: int, bank_end: int) -> list[tuple[int, int, int]]:
    table = TABLE_BASE[VER] - ROM_BASE
    unique = []
    seen = set()
    for i in range(RECORD_COUNT):
        tiles, frames, palette, reserved = struct.unpack_from("<4I", rom, table + i * 16)
        if reserved or not (bank_start <= tiles < frames < palette < bank_end):
            raise ValueError(f"portrait record {i}: invalid pointers or reserved word")
        triple = tiles, frames, palette
        if triple not in seen:
            unique.append(triple)
            seen.add(triple)
    if not unique or unique[0][0] != bank_start or unique[-1][2] + PALETTE_SIZE != bank_end:
        raise ValueError("portrait bank endpoints do not match the table")
    for i, (tiles, frames, palette) in enumerate(unique):
        next_tiles = unique[i + 1][0] if i + 1 < len(unique) else bank_end
        if palette + PALETTE_SIZE != next_tiles:
            raise ValueError(f"portrait {i + 1}: palette does not end at the next resource")
    return unique


def main() -> None:
    if sys.argv[1:] not in ([], ["--index-only"]):
        sys.exit(f"usage: {sys.argv[0]} [--index-only]")
    index_only = sys.argv[1:] == ["--index-only"]
    rom = Path(f"baserom.{VER}.gba").read_bytes()
    banks = [(start, end, source) for start, end, source, name in image_banks(VER) if name == "Portraits"]
    if len(banks) != 1:
        raise ValueError("expected one Portraits image-bank row in regions.us.txt")
    bank_start, bank_end, source = banks[0]
    unique = records(rom, bank_start, bank_end)
    source.mkdir(parents=True, exist_ok=True)
    components = []
    for i, (tiles, frames, palette) in enumerate(unique, 1):
        stem = f"Portrait{i:03d}"
        # Decode every unique image before claiming its bytes as a bank.
        extract_one(rom, tiles, frames, palette)
        for kind, symbol, start, end in (
            ("tiles", f"g{stem}Tiles", tiles, frames),
            ("frames", f"g{stem}Frames", frames, palette),
            ("palette", f"g{stem}Palette", palette, palette + PALETTE_SIZE),
        ):
            filename = f"{stem}.{kind}.bin"
            path = source / filename
            if index_only:
                if not path.is_file():
                    raise ValueError(f"missing {path}; extract portraits first")
            else:
                path.write_bytes(rom[start - ROM_BASE:end - ROM_BASE])
            components.append({"file": filename, "symbol": symbol})
    (source / "bank.json").write_text(json.dumps({"format": 1, "components": components}, indent=2) + "\n")
    print(f"{'indexed' if index_only else 'extracted'} {len(unique)} unique portraits in {source}")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, struct.error) as exc:
        sys.exit(str(exc))
