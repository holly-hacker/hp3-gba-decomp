#!/usr/bin/env python3
"""Extract every room's graphics from the baseroms into data/room_graphics/.

Each room is written as the editable files described in roomfiles.py. Every
room must rebuild to its ROM bytes exactly, in both versions, and the US and
JP contents must be the same; the files come from the US ROM.

data/room_graphics/ is gitignored, same footing as the baserom (AGENTS.md hard
rule 2); extraction overwrites local edits.

Usage: extract_room_graphics.py
"""
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from roomfiles import write_room_dir
from roomgfx import ENTRY_SIZE, ROM_BASE, build_room, read_room

ROOT = Path(__file__).resolve().parents[2]
ROOM_COUNT = 55
OUT = ROOT / "data" / "room_graphics"


def manifest_rows(ver: str):
    """(room table address, {room: name}) from regions.<ver>.txt."""
    table, names = None, {}
    for line in (ROOT / f"regions.{ver}.txt").read_text().splitlines():
        parts = line.split("#", 1)[0].split()
        if parts and parts[-1] == "g_aRoomTable" and parts[0] in ("label", "c-file"):
            table = int(parts[1], 16)
        elif len(parts) == 5 and parts[0] == "asm-file":
            m = re.fullmatch(r"Room(\d\d)Blob", parts[4])
            if m:
                names[int(m.group(1))] = Path(parts[3]).stem
    return table, names


def main() -> None:
    rooms = {}
    names = None
    for ver in ("us", "jp"):
        rom = (ROOT / f"baserom.{ver}.gba").read_bytes()
        table, names_ver = manifest_rows(ver)
        if len(names_ver) != ROOM_COUNT:
            raise SystemExit(f"regions.{ver}.txt does not name all {ROOM_COUNT} rooms")
        names = names or names_ver
        if names != names_ver:
            raise SystemExit("room names differ between versions")
        rooms[ver] = {}
        for n in range(ROOM_COUNT):
            entry = table - ROM_BASE + n * ENTRY_SIZE
            room = read_room(rom, entry)
            start = struct.unpack_from("<I", rom, entry)[0] - ROM_BASE
            data = b"".join(b for _, b in build_room(room))
            if rom[start:start + len(data)] != data:
                raise SystemExit(f"{ver} room {n} ({names[n]}): rebuild differs from the ROM")
            rooms[ver][n] = room
        print(f"{ver}: {ROOM_COUNT} rooms rebuild byte-exact")
    different = [names[n] for n in range(ROOM_COUNT) if rooms["us"][n] != rooms["jp"][n]]
    if different:
        raise SystemExit(f"US and JP differ in: {', '.join(different)}")
    for n in range(ROOM_COUNT):
        write_room_dir(rooms["us"][n], OUT / names[n])
    print(f"wrote {ROOM_COUNT} rooms to {OUT}")


if __name__ == "__main__":
    main()
