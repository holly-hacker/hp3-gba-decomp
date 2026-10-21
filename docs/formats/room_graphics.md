# Room graphics

Each `RoomTableEntry` points at 14 resources: a block map and a block set for
each of four BG layers, the collision behavior table and map, and two
tileset/palette pairs. A room's resources are contiguous and not shared,
and the 55 rooms follow each other in table order. US and JP contain the
same data. The Time-Turner cutscene table reuses rooms 33 and 14.

## Encoding

The ten compressed resources per room re-encode byte for byte: 458 GammaLz,
73 BIOS RLE and 19 BIOS LZ77 in all, 257 of them with the delta flag. The
original tool padded streams with zeros to a word, and a BIOS RLE stream
that already ends on a word gets a whole extra word. A block map with an odd
number of cells is padded with two zero bytes. The tileset layout is in
`tools/graphics/bgtileset.py`. Its tool residue bytes are leftover memory
(zero in about half the tilesets, otherwise text fragments such as `\Wbe` or
`;C:\`) and are kept per tileset.

## Source files

Each room is a `room-graphics` run in `data/graphics/rooms/` (see
[`graphics.md`](graphics.md) "Graphics build format"), in the subdirectory
named by its `dir` setting:

- `tileset_a.png`, `tileset_b.png`: 8-bit indexed tile sheets, 16 tiles per
  row, with the room's 256-color palette as the PNG palette. A pixel is
  `bank * 16 + color number`. The bank is the one the tile's block cells use
  most, the lowest on a tie (203 of 234,979 tiles are drawn with more than
  one bank). Only the color number is data, because the layer files keep
  each cell's own bank. The packer rejects a sheet whose palette lost
  entries and a tile whose pixels mix banks.
- `layer0.json` - `layer3.json`: the block grid, and the blocks (16 tiles
  each, with a tile number, palette bank and `h`/`v` flips).
- `collision.json`: the collision patterns (16 cells, each with a type and a
  layer) and the block grid.
- `room.json`: each resource's codec and delta flag, and the tileset
  residue.

The `RoomGraphics` group labels each room's resources `gRoom<NN>BgMap0`,
`gRoom<NN>BgBlocks0`, ..., `gRoom<NN>PaletteB`, which `src/map/room_table.c`
uses. `just dump-room-graphics` renders each room's BG layers and a merged
view to `extracted/graphics/rooms/` for viewing.
