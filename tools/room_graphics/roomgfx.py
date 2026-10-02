"""Room graphics: the 14 resources the room table points at, as editable data.

A room's resources are contiguous in the ROM, in this order (offsets are the
room table entry's fields): for each of the 4 BG layers a block map (+0x00)
and its block set (+0x04); the collision behavior table (+0x40) and collision
map (+0x44); tileset A (+0x54), palette A (+0x58), tileset B (+0x5C), palette
B (+0x60). See docs/formats/graphics.md, docs/formats/levels.md and
docs/formats/collision.md.

read_room() decodes them from a ROM, build_room() encodes them back.
"""
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "graphics"))
from bgtileset import Tileset, decode_tileset, encode_tileset  # noqa: E402
from decode_gamma_lz import ROM_BASE, _apply_delta_pass  # noqa: E402
from dump_bg_tiles import decode_resource  # noqa: E402
from encode_bios_lz77 import encode_bios_lz77  # noqa: E402
from encode_bios_rle import encode_bios_rle  # noqa: E402
from encode_gamma_lz import _encode_once  # noqa: E402

ENTRY_SIZE = 0x7C
PALETTE_BYTES = 512
FLIPS = ("", "h", "v", "hv")

# (name, room table field offset) in ROM order. Palettes and tilesets are
# handled separately from the compressed resources.
COMPRESSED = [(f"{kind}{n}", n * 16 + (0 if kind == "map" else 4))
              for n in range(4) for kind in ("map", "blocks")] + \
             [("collision_behavior", 0x40), ("collision_map", 0x44)]
CODECS = ("stored", "bios-lz77", "bios-rle", "gamma-lz")
CODEC_TYPE = {0: "stored", 1: "bios-lz77", 3: "bios-rle", 6: "gamma-lz"}


@dataclass
class Block:
    tiles: list[int]
    palettes: list[int]
    flips: list[str]


@dataclass
class Layer:
    grid: list[list[int]]          # block index per 32x32-pixel block, row by row
    blocks: list[Block]


@dataclass
class Collision:
    patterns: list[dict]           # {"types": [16], "layers": [16]}, a 4x4 cell grid
    grid: list[list[int]]          # pattern index per block, the size of layer 0's grid


@dataclass
class RoomGraphics:
    layers: list[Layer]
    collision: Collision
    palettes: list[list[int]]      # two palettes of 256 BGR555 colors
    tilesets: list[Tileset]
    codecs: dict[str, dict] = field(default_factory=dict)   # resource -> {"codec", "delta"}


def _delta_code(data: bytes) -> bytes:
    n = len(data) // 2
    vals = struct.unpack(f"<{n}H", data[:n * 2])
    return struct.pack(f"<{n}H", *[(vals[i] - vals[i - 1]) & 0xFFFF if i else vals[0]
                                  for i in range(n)]) + data[n * 2:]


def encode_resource(data: bytes, codec: str, delta: bool) -> bytes:
    """A dispatcher resource: 4-byte type/size header, then the codec's stream,
    zero-padded as the ROM has it."""
    body = _delta_code(data) if delta else data
    if codec == "stored":
        out = bytes([0x00]) + len(body).to_bytes(3, "little") + body
    elif codec == "bios-rle":
        out = encode_bios_rle(body)
    elif codec == "bios-lz77":
        out = encode_bios_lz77(body)
    elif codec == "gamma-lz":
        return _encode_once(body, delta)
    else:
        raise ValueError(codec)
    out = bytes([out[0] | (0x80 if delta else 0)]) + out[1:]
    # The tool pads to a word; a BIOS RLE stream that already ends on a word
    # gets a whole extra one.
    pad = 4 - len(out) % 4 if codec == "bios-rle" else -len(out) % 4
    return out + bytes(pad)


def _decode_info(rom: bytes, ptr: int) -> tuple[bytes, dict]:
    header = rom[ptr - ROM_BASE]
    codec = CODEC_TYPE[(header >> 4) & 7]
    return decode_resource(rom, "", ptr), {"codec": codec, "delta": bool(header & 0x80)}


# -- resource payloads ---------------------------------------------------------

def parse_map(data: bytes) -> list[list[int]]:
    width, height = struct.unpack_from("<HH", data)
    cells = struct.unpack_from(f"<{width * height}H", data, 4)
    pad = data[4 + 2 * width * height:]
    if pad != bytes(len(pad)) or (4 + 2 * width * height + len(pad)) % 4:
        raise ValueError("unexpected block map tail")
    return [list(cells[y * width:(y + 1) * width]) for y in range(height)]


def build_map(grid: list[list[int]]) -> bytes:
    height, width = len(grid), len(grid[0])
    out = struct.pack("<HH", width, height) + struct.pack(
        f"<{width * height}H", *[c for row in grid for c in row])
    return out + bytes(-len(out) % 4)


def parse_blocks(data: bytes) -> list[Block]:
    count = struct.unpack_from("<I", data)[0]
    if len(data) != 4 + count * 48:
        raise ValueError("unexpected block set size")
    tiles = struct.unpack_from(f"<{count * 16}H", data, 4)
    attrs = data[4 + count * 32:]
    blocks = []
    for i in range(count):
        a = attrs[i * 16:(i + 1) * 16]
        if any(b >> 6 for b in a):
            raise ValueError("unexpected block attribute bits")
        blocks.append(Block(list(tiles[i * 16:(i + 1) * 16]), [b >> 2 & 15 for b in a],
                            [FLIPS[b & 3] for b in a]))
    return blocks


def build_blocks(blocks: list[Block]) -> bytes:
    tiles = [t for b in blocks for t in b.tiles]
    attrs = bytes(FLIPS.index(f) | (p << 2)
                  for b in blocks for p, f in zip(b.palettes, b.flips))
    return struct.pack("<I", len(blocks)) + struct.pack(f"<{len(tiles)}H", *tiles) + attrs


def parse_collision(behavior: bytes, cmap: bytes, width: int, height: int) -> Collision:
    if len(behavior) % 16:
        raise ValueError("unexpected collision behavior size")
    patterns = [{"types": [b & 0x3F for b in behavior[i:i + 16]],
                 "layers": [b >> 6 for b in behavior[i:i + 16]]}
                for i in range(0, len(behavior), 16)]
    count, second = struct.unpack_from("<HH", cmap)
    if count != len(patterns) or second != 0 or len(cmap) != 4 + 2 * width * height:
        raise ValueError("unexpected collision map")
    cells = struct.unpack_from(f"<{width * height}H", cmap, 4)
    return Collision(patterns, [list(cells[y * width:(y + 1) * width]) for y in range(height)])


def build_collision(c: Collision) -> tuple[bytes, bytes]:
    behavior = bytes((layer << 6) | t for p in c.patterns
                     for t, layer in zip(p["types"], p["layers"]))
    cells = [v for row in c.grid for v in row]
    return behavior, struct.pack("<HH", len(c.patterns), 0) + struct.pack(f"<{len(cells)}H", *cells)


# -- whole rooms ---------------------------------------------------------------

def read_room(rom: bytes, entry_off: int) -> RoomGraphics:
    """Decode the room whose table entry starts at file offset entry_off."""
    def ptr(off):
        return struct.unpack_from("<I", rom, entry_off + off)[0]

    raw, codecs = {}, {}
    for name, off in COMPRESSED:
        raw[name], codecs[name] = _decode_info(rom, ptr(off))
    layers = []
    for n in range(4):
        layers.append(Layer(parse_map(raw[f"map{n}"]), parse_blocks(raw[f"blocks{n}"])))
    height, width = len(layers[0].grid), len(layers[0].grid[0])
    collision = parse_collision(raw["collision_behavior"], raw["collision_map"], width, height)
    palettes = []
    for off in (0x58, 0x60):
        data = rom[ptr(off) - ROM_BASE:ptr(off) - ROM_BASE + PALETTE_BYTES]
        palettes.append(list(struct.unpack("<256H", data)))
    tilesets = [decode_tileset(rom, ptr(0x54)), decode_tileset(rom, ptr(0x5C))]
    return RoomGraphics(layers, collision, palettes, tilesets, codecs)


def build_room(room: RoomGraphics) -> list[tuple[str, bytes]]:
    """The room's resources as (name, bytes), in ROM order."""
    payload = {}
    for n, layer in enumerate(room.layers):
        payload[f"map{n}"] = build_map(layer.grid)
        payload[f"blocks{n}"] = build_blocks(layer.blocks)
    payload["collision_behavior"], payload["collision_map"] = build_collision(room.collision)
    sections = []
    for name, _ in COMPRESSED:
        info = room.codecs[name]
        sections.append((name, encode_resource(payload[name], info["codec"], info["delta"])))
    sections.append(("tileset_a", encode_tileset(room.tilesets[0])))
    sections.append(("palette_a", struct.pack("<256H", *room.palettes[0])))
    sections.append(("tileset_b", encode_tileset(room.tilesets[1])))
    sections.append(("palette_b", struct.pack("<256H", *room.palettes[1])))
    order = [n for n, _ in COMPRESSED] + ["tileset_a", "palette_a", "tileset_b", "palette_b"]
    return sorted(sections, key=lambda s: order.index(s[0]))
