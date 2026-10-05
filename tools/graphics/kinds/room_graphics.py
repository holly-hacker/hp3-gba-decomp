"""room-graphics runs: rooms' graphics resources (see
tools/room_graphics/roomgfx.py and docs/formats/room_graphics.md).

Settings: the `rooms` list, in room table order, each naming its `dir`, a
subdirectory of the feature directory holding the editable files described
in roomfiles.py. A room's 14 contiguous resources are labeled g<Name> plus
BgMap0-3, BgBlocks0-3, CollisionBehavior, CollisionMap, TilesetA, PaletteA,
TilesetB and PaletteB.
"""
import re
from pathlib import Path

from roomfiles import ROOM_FILES, read_room_dir, write_room_dir
from roomgfx import ENTRY_SIZE, PALETTE_BYTES, ROM_BASE, build_room, read_room

ROOT = Path(__file__).resolve().parents[3]
ITEMS = "rooms"
OPTIONS = {}
LABELS = {f"map{n}": f"BgMap{n}" for n in range(4)}
LABELS.update({f"blocks{n}": f"BgBlocks{n}" for n in range(4)})
LABELS.update({"collision_behavior": "CollisionBehavior", "collision_map": "CollisionMap",
               "tileset_a": "TilesetA", "palette_a": "PaletteA",
               "tileset_b": "TilesetB", "palette_b": "PaletteB"})


def check(run: dict) -> None:
    for room in run[ITEMS]:
        if set(room) != {"name", "dir"} or not re.fullmatch(r"\w+", room["dir"]):
            raise ValueError(f"{room.get('name')}: expected dir, a subdirectory name")


def files(run: dict) -> list[str]:
    return [room["dir"] for room in run[ITEMS]]


def item_files(room: dict) -> list[str]:
    return [f"{room['dir']}/{f}" for f in ROOM_FILES]


def build(source: Path, settings: dict, room: dict) -> list[tuple[str, bytes]]:
    return [(f"g{room['name']}{LABELS[section]}", data)
            for section, data in build_room(read_room_dir(source / room["dir"]))]


def room_table(ver: str) -> tuple[int, dict[int, str]]:
    """g_aRoomTable's address, and each room's directory name, from the
    RoomNNBlob rows of regions.<ver>.txt."""
    table, names = None, {}
    for line in (ROOT / f"regions.{ver}.txt").read_text().splitlines():
        parts = line.split("#", 1)[0].split()
        if parts and parts[-1] == "g_aRoomTable" and parts[0] in ("label", "c-file"):
            table = int(parts[1], 16)
        elif len(parts) == 5 and parts[0] == "asm-file":
            m = re.fullmatch(r"Room(\d\d)Blob", parts[4])
            if m:
                names[int(m.group(1))] = Path(parts[3]).stem
    if table is None:
        raise ValueError(f"regions.{ver}.txt does not place g_aRoomTable")
    return table, names


def walk(rom: bytes, ver: str, run) -> list[tuple[int, int]]:
    """Each room's resources, which start at its first table pointer and end
    with its palette B, in room table order."""
    table, _ = room_table(ver)
    spans, addr = [], run.start
    for n in range(run.count):
        entry = table - ROM_BASE + n * ENTRY_SIZE
        first, palette_b = (int.from_bytes(rom[entry + off:entry + off + 4], "little") for off in (0, 0x60))
        if first != addr:
            raise ValueError(f"room {n}'s resources do not start at {addr:#010x}")
        spans.append((addr, palette_b + PALETTE_BYTES))
        addr = palette_b + PALETTE_BYTES
    return spans


def extract(rom: bytes, ver: str, run, source: Path, find) -> list[dict]:
    table, dirs = room_table(ver)
    rooms = []
    for n, (start, end) in enumerate(walk(rom, ver, run)):
        room = read_room(rom, table - ROM_BASE + n * ENTRY_SIZE)
        if rom[start - ROM_BASE:end - ROM_BASE] != b"".join(b for _, b in build_room(room)):
            raise ValueError(f"room {n}: rebuilding it does not give the ROM bytes")
        write_room_dir(room, source / dirs[n])
        rooms.append({"name": run.names[n], "dir": dirs[n]})
    return rooms
