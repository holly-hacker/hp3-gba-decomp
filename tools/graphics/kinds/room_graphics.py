"""room-graphics runs: one room's 14 contiguous graphics resources (see
tools/room_graphics/roomgfx.py and docs/formats/room_graphics.md).

Settings: `dir`, the room's subdirectory of the feature directory, holding
the editable files described in roomfiles.py. The run is named
Room<NN>Graphics after its room table entry; its resources are labeled
Room<NN> plus BgMap0-3, BgBlocks0-3, CollisionBehavior, CollisionMap,
TilesetA, PaletteA, TilesetB and PaletteB.
"""
import re
from pathlib import Path

from roomfiles import ROOM_FILES, read_room_dir, write_room_dir
from roomgfx import ENTRY_SIZE, ROM_BASE, build_room, read_room

ROOT = Path(__file__).resolve().parents[3]
ITEMS = None
NAME = re.compile(r"Room(\d\d)Graphics")
LABELS = {f"map{n}": f"BgMap{n}" for n in range(4)}
LABELS.update({f"blocks{n}": f"BgBlocks{n}" for n in range(4)})
LABELS.update({"collision_behavior": "CollisionBehavior", "collision_map": "CollisionMap",
               "tileset_a": "TilesetA", "palette_a": "PaletteA",
               "tileset_b": "TilesetB", "palette_b": "PaletteB"})


def check(run: dict) -> None:
    if set(run) != {"dir"} or not re.fullmatch(r"\w+", run["dir"]):
        raise ValueError("expected dir, a subdirectory name")


def files(run: dict) -> list[str]:
    return [run["dir"]]


def item_files(run: dict, item: dict) -> list[str]:
    return [f"{run['dir']}/{f}" for f in ROOM_FILES]


def build(source: Path, name: str, settings: dict, item: dict) -> list[tuple[str, bytes]]:
    if not NAME.fullmatch(name):
        raise ValueError(f"{name}: a room-graphics run is named Room<NN>Graphics")
    prefix = name.removesuffix("Graphics")
    return [(prefix + LABELS[section], data) for section, data in build_room(read_room_dir(source / settings["dir"]))]


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


def extract(rom: bytes, ver: str, start: int, end: int, name: str, source: Path) -> dict:
    m = NAME.fullmatch(name)
    if not m:
        raise ValueError(f"{name}: a room-graphics run is named Room<NN>Graphics")
    table, names = room_table(ver)
    n = int(m.group(1))
    room = read_room(rom, table - ROM_BASE + n * ENTRY_SIZE)
    data = b"".join(b for _, b in build_room(room))
    if rom[start - ROM_BASE:end - ROM_BASE] != data:
        raise ValueError(f"{name}: rebuilding the room does not give the ROM bytes at {start:#010x}-{end:#010x}")
    write_room_dir(room, source / names[n])
    return {"dir": names[n]}
