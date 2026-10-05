"""The editable files of one room's graphics, see tools/room_graphics/roomgfx.py.

  tileset_a.png, tileset_b.png   8-bit indexed tile sheet, 16 tiles per row. The
                                 PNG palette is the room's 256-color palette
                                 (BGR555 channels expanded to 8 bits), 16 banks
                                 of 16. A pixel is bank * 16 + color number,
                                 where the bank is the one the tile's block
                                 cells mostly use, so the sheet shows the real
                                 colors. Only the color number is data: the
                                 layer files keep each cell's own bank.
  layer0.json .. layer3.json     block grid and block set of each BG layer
  collision.json                 collision patterns and the block grid
  room.json                      the codec of each resource and the values the
                                 original tool left in padding
"""
import collections
import json
import re
from pathlib import Path

from PIL import Image

from roomgfx import COMPRESSED, Block, Collision, Layer, RoomGraphics
from bgtileset import Tileset

ROOM_FILES = ("tileset_a.png", "tileset_b.png", "layer0.json", "layer1.json", "layer2.json", "layer3.json",
              "collision.json", "room.json")
TILES_PER_ROW = 16
SHEET_WIDTH = TILES_PER_ROW * 8


def dump_json(obj) -> str:
    text = json.dumps(obj, indent=1)
    return re.sub(r"\[\s+([^\[\]{}]*?)\s+\]", lambda m: "[" + re.sub(r"\s+", " ", m.group(1)) + "]", text) + "\n"


def _rgb(color: int) -> tuple[int, int, int]:
    if color >> 15:
        raise ValueError("palette color uses bit 15")
    return tuple((v << 3) | (v >> 2) for v in (color & 31, (color >> 5) & 31, (color >> 10) & 31))


def _color(rgb: tuple[int, int, int]) -> int:
    r, g, b = (v >> 3 for v in rgb)
    return r | (g << 5) | (b << 10)


# Tileset A is drawn by layers 0 and 3, tileset B by layers 1 and 2.
TILESET_LAYERS = {"a": (0, 3), "b": (1, 2)}


def tile_banks(room: RoomGraphics, key: str) -> list[int]:
    """The palette bank each tile is mostly drawn with (the lowest on a tie)."""
    uses = collections.defaultdict(collections.Counter)
    for n in TILESET_LAYERS[key]:
        for block in room.layers[n].blocks:
            for tile, bank in zip(block.tiles, block.palettes):
                uses[tile][bank] += 1
    banks = []
    for tile in range(len(room.tilesets["ab".index(key)].tiles)):
        counts = uses.get(tile)
        banks.append(min(counts, key=lambda b: (-counts[b], b)) if counts else 0)
    return banks


def write_tileset(path: Path, tileset: Tileset, palette: list[int], banks: list[int]) -> None:
    """Tile sheet with the room palette as its PNG palette."""
    count = len(tileset.tiles)
    rows = (count + TILES_PER_ROW - 1) // TILES_PER_ROW
    pixels = bytearray(SHEET_WIDTH * rows * 8)
    for index, tile in enumerate(tileset.tiles):
        base_x, base_y = (index % TILES_PER_ROW) * 8, (index // TILES_PER_ROW) * 8
        for y in range(8):
            for x in range(4):
                byte = tile[y * 4 + x]
                at = (base_y + y) * SHEET_WIDTH + base_x + x * 2
                pixels[at] = banks[index] * 16 + (byte & 15)
                pixels[at + 1] = banks[index] * 16 + (byte >> 4)
    image = Image.new("P", (SHEET_WIDTH, rows * 8))
    image.putdata(bytes(pixels))
    image.putpalette([c for color in palette for c in _rgb(color)])
    image.save(path)


def read_tileset(path: Path, count: int) -> tuple[list[bytes], list[int]]:
    """The tiles of a sheet written by write_tileset, and its palette."""
    image = Image.open(path)
    if image.mode != "P" or image.width != SHEET_WIDTH:
        raise ValueError(f"{path}: a tile sheet is a {SHEET_WIDTH}-pixel-wide indexed image")
    raw = image.palette.palette
    if image.palette.mode != "RGB" or len(raw) != 768:
        raise ValueError(f"{path}: the palette must keep all 256 entries (an editor may have "
                         "dropped the unused ones)")
    palette = [_color((raw[i], raw[i + 1], raw[i + 2])) for i in range(0, 768, 3)]
    pixels = bytes(image.getdata())
    tiles = []
    for index in range(count):
        base_x, base_y = (index % TILES_PER_ROW) * 8, (index // TILES_PER_ROW) * 8
        tile = bytearray()
        banks = set()
        for y in range(8):
            at = (base_y + y) * SHEET_WIDTH + base_x
            for x in range(0, 8, 2):
                tile.append((pixels[at + x] & 15) | ((pixels[at + x + 1] & 15) << 4))
                banks.update((pixels[at + x] >> 4, pixels[at + x + 1] >> 4))
        if len(banks) != 1:
            raise ValueError(f"{path}: tile {index} mixes colors of palette banks "
                             f"{sorted(banks)}; paint a tile with one bank's 16 colors")
        tiles.append(bytes(tile))
    return tiles, palette


def write_room_dir(room: RoomGraphics, path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)
    for n, layer in enumerate(room.layers):
        blocks = [{"tiles": b.tiles, "palettes": b.palettes, "flips": b.flips} for b in layer.blocks]
        (path / f"layer{n}.json").write_text(dump_json({"grid": layer.grid, "blocks": blocks}))
    (path / "collision.json").write_text(dump_json(
        {"patterns": room.collision.patterns, "grid": room.collision.grid}))
    for key, palette, tileset in zip("ab", room.palettes, room.tilesets):
        write_tileset(path / f"tileset_{key}.png", tileset, palette, tile_banks(room, key))
    bank = {"format": 1, "codecs": room.codecs, "tilesets": {}}
    for key, tileset in zip("ab", room.tilesets):
        bank["tilesets"][key] = {
            "tile_count": len(tileset.tiles),
            "offset_table_residue": int.from_bytes(tileset.offset_table_residue, "little"),
            "head_residue": int.from_bytes(tileset.head_residue, "little"),
            "end_residue": int.from_bytes(tileset.end_residue, "little"),
        }
    (path / "room.json").write_text(dump_json(bank))


def read_room_dir(path: Path) -> RoomGraphics:
    bank = json.loads((path / "room.json").read_text())
    layers = []
    for n in range(4):
        data = json.loads((path / f"layer{n}.json").read_text())
        layers.append(Layer(data["grid"], [Block(b["tiles"], b["palettes"], b["flips"])
                                           for b in data["blocks"]]))
    data = json.loads((path / "collision.json").read_text())
    collision = Collision(data["patterns"], data["grid"])
    palettes, tilesets = [], []
    for key in "ab":
        info = bank["tilesets"][key]
        tiles, palette = read_tileset(path / f"tileset_{key}.png", info["tile_count"])
        palettes.append(palette)
        tilesets.append(Tileset(
            tiles,
            info["offset_table_residue"].to_bytes(2, "little"),
            info["head_residue"].to_bytes(4, "little"),
            info["end_residue"].to_bytes(4, "little")))
    return RoomGraphics(layers, collision, palettes, tilesets, bank["codecs"])
