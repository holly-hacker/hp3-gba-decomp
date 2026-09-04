#!/usr/bin/env python3
"""Render every entry in the character-portrait table (US 0x0804C61C, 72
records, reachable via the debug portrait-viewer menu,
InitializeDebugPortraitsMenu/0x0800B5A8, but the records themselves are
the game's normal dialog portraits) as a transparent-background PNG.

Each 16-byte record is {pTileGfx, pFrameData, pPalette, 0}. pTileGfx is
type-4-compressed OBJ tile data (see tools/graphics/decode_type4.py);
pFrameData is an uncompressed per-object animation/frame-and-cell
descriptor, read directly (never routed through the resource-compression
dispatcher despite superficially looking like it could be); pPalette is
a raw, uncompressed 256-entry BGR555 table (no header at all).

Frame 0's cell table gives each OAM cell's {shape, size, relative tile
offset, relative X/Y offset} -- confirmed against real OAM captured live
via mGBA (record 1: 9 cells, tile offsets and shape/size bits matched
exactly once the shape/size nibbles below were un-swapped, and the
decoded tile bytes matched real OBJ VRAM byte-for-byte). Cells are laid
out back-to-back in the decompressed tile stream with no padding --
confirmed by the cell-to-cell tile deltas exactly equaling each cell's
own w*h tile count, not by the GBA's 2D OBJ-mapping row stride (which
would apply to *absolute* VRAM tile addressing, not to how this
resource's own bytes are laid out). Each cell's on-screen X/Y offset is
a signed 9-bit field split across b0/b1 (X) and b1/b2 (Y) of its 4-byte
record (same bytes WriteObjectOamCells, US 0x08002C18, decodes into a
live OAM entry's position) -- confirmed against record 1's real OAM
X/Y: the relative deltas between cells matched exactly, up to a
constant per-record offset (the object's own arbitrary on-screen
anchor at capture time, normalized out here by subtracting each
record's own minimum). Palette index 0 is the hardware-fixed OBJ
transparent index for 8bpp sprites and is rendered as alpha 0.

Usage: extract_portraits.py <ver> <out_dir>
Writes one <out_dir>/portrait_<NN>.png per record (RGBA, index 0 =
transparent), skipping (with a warning on stderr) any record whose
pointers or type-4 header don't validate.
"""
import struct
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).parent))
from decode_type4 import decode_type4, CODEC_ADDR, CODEC_LEN  # noqa: E402

ROM_BASE = 0x08000000
TABLE_BASE = {"us": 0x0804C61C}
RECORD_COUNT = 72

SHAPE_SIZE_TILES = {
    (0, 0): (1, 1), (0, 1): (2, 2), (0, 2): (4, 4), (0, 3): (8, 8),
    (1, 0): (2, 1), (1, 1): (4, 1), (1, 2): (4, 2), (1, 3): (8, 4),
    (2, 0): (1, 2), (2, 1): (1, 4), (2, 2): (2, 4), (2, 3): (4, 8),
}


def bgr555_to_rgb(v: int):
    r = (v & 0x1F) * 255 // 31
    g = ((v >> 5) & 0x1F) * 255 // 31
    b = ((v >> 10) & 0x1F) * 255 // 31
    return (r, g, b)


def u8(rom: bytes, a: int) -> int:
    return rom[a - ROM_BASE]


def u16(rom: bytes, a: int) -> int:
    return struct.unpack_from("<H", rom, a - ROM_BASE)[0]


def u32(rom: bytes, a: int) -> int:
    return struct.unpack_from("<I", rom, a - ROM_BASE)[0]


def sign9(v: int) -> int:
    v &= 0x1FF
    return v - 512 if v >= 256 else v


def read_cells(rom: bytes, ptr2: int, frame: int = 0):
    """Returns (cell list of {shape, size, w, h, rel_tile, x, y}, total tile area).
    x/y are relative pixel offsets, normalized so the topmost/leftmost cell
    sits at 0 (the real per-record additive constant is the object's own
    arbitrary on-screen anchor and carries no information for a static
    extraction)."""
    tbl_val = u16(rom, ptr2 + 0xC + frame * 2)
    frame_base = ptr2 + tbl_val + 0xC
    n_at_a = u8(rom, ptr2 + 0xA)
    part_count = u8(rom, ptr2 + 0xB)
    cell_count = u8(rom, frame_base) & 0x1F
    cells_base = frame_base + n_at_a * 2 + part_count * 6 + 0xA

    cells = []
    rel_tile = 0
    for i in range(cell_count):
        p = cells_base + i * 4
        b0, b1, b2, b3 = (u8(rom, p), u8(rom, p + 1), u8(rom, p + 2), u8(rom, p + 3))
        size = (b2 & 0xF) >> 2
        shape = (b2 & 0x3F) >> 4
        wh = SHAPE_SIZE_TILES.get((shape, size))
        if wh is None:
            break  # invalid shape code -- past the real cell table
        w, h = wh
        x = sign9(((b1 & 1) << 8) | b0)
        y = sign9(((b2 & 3) << 7) | (b1 >> 1))
        cells.append(dict(w=w, h=h, rel_tile=rel_tile, x=x, y=y))
        rel_tile += w * h

    if cells:
        min_x = min(c["x"] for c in cells)
        min_y = min(c["y"] for c in cells)
        for c in cells:
            c["x"] -= min_x
            c["y"] -= min_y
    return cells, rel_tile


def extract_one(rom: bytes, ptr1: int, ptr2: int, ptr3: int, codec_addr: int):
    hdr = u32(rom, ptr1)
    if (hdr & 0xFF) >> 4 != 7:
        raise ValueError(f"ptr1 {ptr1:#x} header nibble != 7 (type-4)")
    decl_size = hdr >> 8

    cells, total_tiles_needed = read_cells(rom, ptr2)
    if not cells:
        raise ValueError("no valid cells")

    tiledata = decode_type4(rom, ptr1 + 4, codec_addr)[:decl_size]
    if total_tiles_needed * 64 > len(tiledata):
        raise ValueError(f"cells need {total_tiles_needed} tiles but only "
                          f"{len(tiledata) // 64} decoded")

    colors = struct.unpack_from("<256H", rom, ptr3 - ROM_BASE)
    pal = [bgr555_to_rgb(v) for v in colors]

    canvas_w = max(c["x"] + c["w"] * 8 for c in cells)
    canvas_h = max(c["y"] + c["h"] * 8 for c in cells)

    img = Image.new("RGBA", (canvas_w, canvas_h), (0, 0, 0, 0))
    px = img.load()
    for c in cells:
        for t in range(c["w"] * c["h"]):
            off = (c["rel_tile"] + t) * 64
            tile_px = tiledata[off:off + 64]
            tx, ty = c["x"] + (t % c["w"]) * 8, c["y"] + (t // c["w"]) * 8
            for r in range(8):
                for col in range(8):
                    v = tile_px[r * 8 + col]
                    if v != 0:
                        rgb = pal[v]
                        px[tx + col, ty + r] = (rgb[0], rgb[1], rgb[2], 255)
    return img


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <out_dir>")
    ver, out_dir = sys.argv[1], Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()

    table_base = TABLE_BASE[ver]
    codec_addr = CODEC_ADDR[ver]

    ok, failed = 0, 0
    for i in range(RECORD_COUNT):
        rec = table_base + i * 16
        ptr1, ptr2, ptr3, zero = struct.unpack_from("<4I", rom, rec - ROM_BASE)
        try:
            if zero != 0 or not all(ROM_BASE <= p < 0x0A000000 for p in (ptr1, ptr2, ptr3)):
                raise ValueError("bad pointers")
            img = extract_one(rom, ptr1, ptr2, ptr3, codec_addr)
            img.save(out_dir / f"portrait_{i:02d}.png")
            ok += 1
        except Exception as e:  # noqa: BLE001 -- report and keep going
            print(f"record {i}: FAILED ({e})", file=sys.stderr)
            failed += 1

    print(f"extracted {ok}/{RECORD_COUNT} portraits to {out_dir} ({failed} failed)")


if __name__ == "__main__":
    main()
