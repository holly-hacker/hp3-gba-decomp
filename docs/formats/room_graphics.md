# Room graphics

The 14 resources each room-table entry points at (see [`levels.md`](levels.md)):
four BG layers (a block map and a block set each), the collision behavior table
and collision map, and two tileset/palette pairs. Formats of the pieces are in
[`graphics.md`](graphics.md) and [`collision.md`](collision.md); this document
covers how they sit in the ROM and how they are built.

## ROM layout (PROVEN, US and JP)

A room's resources are contiguous and unshared, in this order:

| Room table offset | Resource |
|---|---|
| `+0x00`, `+0x04` | layer 0 block map, block set |
| `+0x10`, `+0x14`; `+0x20`, `+0x24`; `+0x30`, `+0x34` | layers 1-3 |
| `+0x40`, `+0x44` | collision behavior table, collision map |
| `+0x54` | tileset A |
| `+0x58` | palette A (512 bytes) |
| `+0x5C` | tileset B |
| `+0x60` | palette B (512 bytes) |

The 55 rooms follow each other in table order with no gap, US
`0x081DB29C`-`0x08854EE0`, JP `0x081DB0CC`-`0x08854D10`. US and JP contain the
same data.

## Compressed resources

The ten block maps, block sets and collision resources are dispatcher
resources (see "Compressed resources" in `graphics.md`): 458 GammaLz, 73 BIOS
RLE and 19 BIOS LZ77, with the delta flag set on 257. All re-encode byte for
byte. The LZ77 encoder takes the longest match (at most 18 bytes, at least 3),
the nearest on a tie, and never distance 1. The tool pads streams with zeros to
a word; a BIOS RLE stream that already ends on a word gets a whole extra word.
A block map with an odd number of cells is padded with two zero bytes. The
codec of each resource is recorded per room.

## Tilesets

```
u16 size            aligned size of the offset table resource + 4
u16 tile_count
resource            tile offset table: stored (type 0) or GammaLz (type 6),
                    whichever is smaller; u16 tile_count, then one length in
                    bits per tile (one byte 0x20 + n, or 0xFF and a big-endian
                    u16), then 2 bytes of tool residue
zero padding        to a word
4 bytes             tool residue
u32  0x20 | tile_count * 32 << 8
292 bytes           canonical Huffman table: count[18], base[18], symbol[256]
bitstream           each tile's 32 bytes as codes, MSB-first codes packed
                    LSB-first into little-endian words, padded to a word
4 bytes             tool residue
```

The code lengths are plain Huffman lengths of the byte frequencies over all
tiles of the set; codes are assigned canonically by (length, symbol). The three
residue values are leftover memory of the tool that built the ROM (zero in about
half the tilesets, otherwise text fragments such as `\Wbe` or `;C:\`); they are
kept per tileset. All 110 tilesets of each version re-encode exactly
(`tools/graphics/bgtileset.py`).

## Source files

Each room is a `room-graphics` run in `data/graphics/rooms/` (see
[`graphics.md`](graphics.md) "Graphics build format") whose `dir` setting
names its subdirectory, `<room_name>/`:

- `tileset_a.png`, `tileset_b.png`: 8-bit indexed tile sheets, 16 tiles per
  row, with the room's 256-color palette (16 banks of 16) as the PNG palette. A
  pixel is `bank * 16 + color number`, where the bank is the one the tile's
  block cells use most (the lowest on a tie; 203 of 234,979 tiles are drawn
  with more than one bank), so the sheet shows the tile's real colors. Only the
  color number is data; the layer files keep each cell's own bank. The packer
  rejects a sheet whose palette lost entries and a tile whose pixels mix banks.
- `layer0.json` - `layer3.json`: the block grid and the blocks (16 tiles, each
  with a tile number, palette bank and `h`/`v` flips).
- `collision.json`: the collision patterns (16 cells with a type and a layer)
  and the block grid.
- `room.json`: each resource's codec and delta flag, and the tileset residue.

One `room-graphics <start> <end> data/graphics/rooms Room<NN>Graphics` row per
room claims the whole range; packing encodes it and labels each resource
(`Room<NN>BgMap0`, `Room<NN>BgBlocks0`, `Room<NN>CollisionBehavior`,
`Room<NN>CollisionMap`, `Room<NN>TilesetA`, `Room<NN>PaletteA`, ...), which
`src/room/room_table.c` (`g_aRoomTable`) refers to, through
`include/gen/graphics/rooms.h`. Code: `tools/room_graphics/` and
`tools/graphics/kinds/room_graphics.py`.

`just dump-room-graphics` (`tools/graphics/dump_bg_tiles.py`) renders every room's
assembled BG layers and a merged view to `extracted/graphics/rooms/`, straight
from the baserom. It is a viewing aid, not build input.

The Time-Turner cutscene's two-entry table (`g_aTimeTurnerCutsceneRoomTable`,
`src/room/time_turner_room_table.c`) uses the same entry layout and no data of
its own: entry 0 refers to the resources of room 33 and entry 1 to those of room
14, with its own music and encounter values. The small coordinate table that
follows it is still raw.
