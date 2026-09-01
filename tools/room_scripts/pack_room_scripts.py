#!/usr/bin/env python3
"""Reads data/room_scripts/ (curated, editable room-script text, see
extract_room_scripts.py) back and verifies it re-encodes to exactly the
bytes the baserom stores for each room's chains.

Unlike tools/battle_scripts/'s pack_battle_scripts.py, this does NOT
emit build assembly -- the room table isn't a regions.<ver>.txt region
yet (see docs/formats/levels.md's "Not yet located"), so there's
nowhere in the real build to place packed chains. This instead re-runs
the same address math extract_room_scripts.py used to locate each
room's chains in the baserom, and confirms encode_chain(parse_chain_text(...))
reproduces those bytes exactly -- the round-trip a real pack step will
rely on once the room table has a manifest row.

Usage: pack_room_scripts.py <ver>
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from room_scripts_codec import encode_chain, parse_chain_text
from extract_room_scripts import ROM_BASE, ROOM_TABLE_ADDR, switch_state_chains, u32, ROOM_TABLE_STRIDE, ROOM_RESOURCE_BLOB_OFFSET, ROOM_COUNT


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    if ver not in ROOM_TABLE_ADDR:
        sys.exit(f"room table address not yet confirmed for ver={ver!r} (US only so far)")

    rom = Path(f"baserom.{ver}.gba").read_bytes()
    data_root = Path("data/room_scripts") / ver
    if not data_root.is_dir():
        sys.exit(f"{data_root} not found -- run `just extract-room-scripts {ver}` first")

    room_count, chain_count, mismatches = 0, 0, []
    for room_dir in sorted(data_root.iterdir()):
        if not room_dir.is_dir():
            continue
        room_count += 1
        idx = int(room_dir.name.split("_", 1)[0])
        blob_addr = u32(rom, ROOM_TABLE_ADDR[ver] + idx * ROOM_TABLE_STRIDE + ROOM_RESOURCE_BLOB_OFFSET)
        real_chains = switch_state_chains(rom, blob_addr)

        filenames = json.loads((room_dir / "index.json").read_text())
        if len(filenames) != len(real_chains):
            mismatches.append(f"{room_dir.name}: {len(filenames)} files, baserom has {len(real_chains)} chains")
            continue

        for chain_idx, filename in enumerate(filenames):
            chain_count += 1
            instructions = parse_chain_text((room_dir / filename).read_text())
            packed = encode_chain(instructions)
            if packed != real_chains[chain_idx]:
                mismatches.append(f"{room_dir.name}/{filename}: {len(packed)} bytes packed, "
                                   f"{len(real_chains[chain_idx])} bytes in baserom, content differs")

    if mismatches:
        print(f"FAILED: {len(mismatches)} mismatch(es) out of {chain_count} chains across {room_count} rooms", file=sys.stderr)
        for m in mismatches:
            print(f"  {m}", file=sys.stderr)
        sys.exit(1)

    print(f"OK: {chain_count} chains across {room_count} rooms round-trip byte-exact", file=sys.stderr)


if __name__ == "__main__":
    main()
