#!/usr/bin/env python3
"""Render a room's BG layers (walls/floor/props/foreground) as PNGs for
visual inspection, plus an alpha-composited merged view. See
docs/formats/graphics.md's "On-demand per-tile BG streaming" section for
the format this decodes -- user-confirmed against real gameplay for
rooms 0x28/0x26/0x27/0x24, structurally checked for the rest.

Research/debugging aid only -- NOT build input, mirrors
dump_collision.py's role. US only (no ver subdirectory in the output --
no reason to believe JP has different graphics content here, only
possibly different addresses).

Real BG palette: level-table field `+0x58` is a raw, uncompressed
256-color (16 banks x 16, BGR555) array -- confirmed byte-exact against
a live mGBA memory dump. See docs/formats/graphics.md.

Filename convention matches tools/collision/dump_collision.py: room name
decoded the same way, sanitized the same way (idx:02d_Room_Name).

Usage: dump_bg_tiles.py <ver>   (renders all 55 rooms)
  writes extracted/graphics/rooms/bg_<NN>_<Room_Name>.png
  and    extracted/graphics/rooms/layers/bg_<NN>_<Room_Name>_layer<N>.png
  (name comes last-ish deliberately -- sorts each room's layers/merged
  file together, rather than grouping all layer0s across every room)
"""
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from decode_bgtile import BgTileDecoder, build_tile_offsets, CODEC_ADDR
from decode_type6 import decode_type6, CODEC_ADDR as TYPE6_CODEC_ADDR, _apply_delta_pass
from decode_bios import DECODERS

sys.path.insert(0, str(Path(__file__).parent.parent / "text"))
from decode_dialog_text import decode_dialog_text

from PIL import Image

ROM_BASE = 0x08000000
TABLE_BASE = {"us": 0x08063C8C}
STRIDE = 0x7C
ROOM_COUNT = 55


def read_palette(rom: bytes, palette_ptr: int) -> list[int]:
    off = palette_ptr - ROM_BASE
    colors = list(struct.unpack_from("<256H", rom, off))
    colors[0] = 0  # backdrop color, force-overwritten separately every room load
    return colors


def decode_resource(rom: bytes, ver: str, hdr_addr: int) -> bytes:
    """Generic dispatcher-header decode: hdr_addr is the resource's own
    4-byte type/size header (sub_0801DD90's convention).

    The dispatcher applies a delta-decode post-pass (sub_0801DF48,
    in-place running sum over the output as u16[]) whenever byte0 bit 7
    is set -- confirmed from sub_0801DD90's real disassembly to run
    unconditionally after every type (0-8), not just type 6. Type 6 gets
    this from decode_type6() internally; every other type needs it
    applied here, since decode_bios.py's raw decoders have no dispatcher
    context to check the bit against."""
    off = hdr_addr - ROM_BASE
    type_nibble = (rom[off] >> 4) & 7
    extra_pass = bool(rom[off] & 0x80)
    size = rom[off + 1] | (rom[off + 2] << 8) | (rom[off + 3] << 16)
    if type_nibble == 0:
        out = rom[off + 4: off + 4 + size]
    elif type_nibble == 6:
        return decode_type6(rom, hdr_addr, TYPE6_CODEC_ADDR[ver])  # applies its own extra_pass
    else:
        decoder = DECODERS.get(type_nibble)
        if decoder is None:
            raise ValueError(f"{hdr_addr:#010x}: unhandled type nibble {type_nibble:#x}")
        out = decoder(rom, hdr_addr)
    return _apply_delta_pass(out) if extra_pass else out


def decode_tileset(rom: bytes, ver: str, resource_ptr: int):
    """Returns (offsets, context_bytes) for a dwBgTilesetA/B resource."""
    off = resource_ptr - ROM_BASE
    size_field, tile_count = struct.unpack_from("<HH", rom, off)
    blob_base = resource_ptr + size_field + 8
    offset_table = decode_resource(rom, ver, resource_ptr + 4)
    offsets = build_tile_offsets(blob_base, offset_table, tile_count)
    context = rom[blob_base - ROM_BASE: blob_base - ROM_BASE + 292]
    return offsets, context


def decode_layer(rom: bytes, ver: str, entry_addr: int, layer: int):
    """Returns (block_map, W_blocks, H_blocks, tile_id_array, pal_array)."""
    off = entry_addr - ROM_BASE + layer * 0x10
    block_ptr, extra_ptr = struct.unpack_from("<II", rom, off)

    block_data = decode_resource(rom, ver, block_ptr)
    W_blocks, H_blocks = struct.unpack_from("<HH", block_data, 0)
    block_map = struct.unpack_from(f"<{W_blocks*H_blocks}H", block_data, 4)

    extra_data = decode_resource(rom, ver, extra_ptr)
    block_count = struct.unpack_from("<I", extra_data, 0)[0]
    tile_id_array = extra_data[4: 4 + block_count * 32]
    pal_array = extra_data[4 + block_count * 32: 4 + block_count * 32 + block_count * 16]
    return block_map, W_blocks, H_blocks, tile_id_array, pal_array


def bgr555_to_rgb(v: int):
    r = (v & 0x1F) * 255 // 31
    g = ((v >> 5) & 0x1F) * 255 // 31
    b = ((v >> 10) & 0x1F) * 255 // 31
    return (r, g, b)


def render_layer(rom: bytes, ver: str, entry_addr: int, layer: int, offsetsA, contextA, decoderA, offsetsB, contextB, decoderB, palette_raw):
    block_map, W_blocks, H_blocks, tile_id_array, pal_array = decode_layer(rom, ver, entry_addr, layer)
    tileset = "A" if layer in (0, 3) else "B"
    offsets, context, decoder = (offsetsA, contextA, decoderA) if tileset == "A" else (offsetsB, contextB, decoderB)

    palettes = [[bgr555_to_rgb(palette_raw[bank * 16 + i]) for i in range(16)] for bank in range(16)]

    # RGBA: palette index 0 is the GBA "see-through" convention for BG
    # tiles (regardless of what color is stored there) -- transparent,
    # not opaque, so lower layers/backdrop show through.
    W_tiles, H_tiles = W_blocks * 4, H_blocks * 4
    img = Image.new("RGBA", (W_tiles * 8, H_tiles * 8), (0, 0, 0, 0))
    tile_cache = {}

    for ty in range(H_tiles):
        blockY, subY = divmod(ty, 4)
        for tx in range(W_tiles):
            blockX, subX = divmod(tx, 4)
            blk = block_map[blockY * W_blocks + blockX]
            sub_index = subY * 4 + subX
            tile_id = struct.unpack_from("<H", tile_id_array, (blk * 16 + sub_index) * 2)[0]
            pal_byte = pal_array[blk * 16 + sub_index]
            hflip, vflip, bank = pal_byte & 1, (pal_byte >> 1) & 1, (pal_byte >> 2) & 0xF

            if tile_id not in tile_cache:
                tile_cache[tile_id] = decoder.decode(offsets[tile_id], context)
            tb = tile_cache[tile_id]
            pal = palettes[bank]
            px, py = tx * 8, ty * 8
            idxb = 0
            for y in range(8):
                for xp in range(0, 8, 2):
                    byte = tb[idxb]
                    idxb += 1
                    lo, hi = byte & 0xF, (byte >> 4) & 0xF
                    px0 = xp if not hflip else 7 - xp
                    px1 = xp + 1 if not hflip else 6 - xp
                    py_ = y if not vflip else 7 - y
                    if lo:
                        img.putpixel((px + px0, py + py_), (*pal[lo], 255))
                    if hi:
                        img.putpixel((px + px1, py + py_), (*pal[hi], 255))
    return img


# Stacking order bottom-to-top, per the user-confirmed hardware mapping
# (level-table layer -> hardware BG): 0->BG3 (main), 2->BG2 (props),
# 1->BG1 (drawn over the player), 3->BG0. NOT literal 0,1,2,3 order --
# BG1/BG2 draw in the opposite order from their level-table indices.
MERGE_ORDER = [0, 2, 1, 3]


def dump_room(rom: bytes, ver: str, room_index: int, name: str, out_dir: Path):
    """out_dir is extracted/graphics/rooms; per-layer PNGs go in its
    layers/ subdirectory, the merged composite directly in out_dir."""
    entry_addr = TABLE_BASE[ver] + room_index * STRIDE
    off = entry_addr - ROM_BASE
    tileset_a_ptr = struct.unpack_from("<I", rom, off + 0x54)[0]
    tileset_b_ptr = struct.unpack_from("<I", rom, off + 0x5C)[0]
    offsetsA, contextA = decode_tileset(rom, ver, tileset_a_ptr)
    offsetsB, contextB = decode_tileset(rom, ver, tileset_b_ptr)
    palette_ptr = struct.unpack_from("<I", rom, off + 0x58)[0]
    palette_raw = read_palette(rom, palette_ptr)

    # One Unicorn instance per tileset, reused across every tile in every
    # layer -- re-mapping/re-writing the ~16MB ROM per tile (the original
    # approach) made whole-room extraction extremely slow for no benefit.
    decoderA = BgTileDecoder(rom, CODEC_ADDR[ver])
    decoderB = BgTileDecoder(rom, CODEC_ADDR[ver])

    layers_dir = out_dir / "layers"
    layers_dir.mkdir(parents=True, exist_ok=True)
    layer_imgs = {}
    for layer in range(4):
        img = render_layer(rom, ver, entry_addr, layer, offsetsA, contextA, decoderA, offsetsB, contextB, decoderB, palette_raw)
        layer_imgs[layer] = img
        out = img.resize((img.width * 2, img.height * 2), Image.NEAREST)
        out.save(layers_dir / f"bg_{name}_layer{layer}.png")

    # backdrop: palette index 0 is force-set to black (see read_palette)
    # -- what shows through where every layer is transparent.
    merged = Image.new("RGBA", layer_imgs[0].size, (0, 0, 0, 255))
    for layer in MERGE_ORDER:
        merged.alpha_composite(layer_imgs[layer])
    merged = merged.resize((merged.width * 2, merged.height * 2), Image.NEAREST)
    merged.save(out_dir / f"bg_{name}.png")


def sanitize(name: str, idx: int) -> str:
    """Same convention as tools/collision/dump_collision.py's sanitize()
    -- keep filenames consistent across subsystems."""
    s = re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_")
    return f"{idx:02d}_{s or 'room'}"


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    if ver not in TABLE_BASE:
        sys.exit(f"room table address not yet confirmed for ver={ver!r} (US only so far)")
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()

    try:
        room_names = [decode_dialog_text(rom, 0, 0x54A + i).rstrip(b"\x00").decode("latin-1", "replace")
                      for i in range(ROOM_COUNT)]
    except Exception as e:
        print(f"room-name decode failed, using room<N>: {e}", file=sys.stderr)
        room_names = [f"room{i}" for i in range(ROOM_COUNT)]

    # No ver subdirectory: no reason to believe JP has different graphics
    # content here, only possibly different addresses.
    out_dir = Path("extracted/graphics/rooms")
    out_dir.mkdir(parents=True, exist_ok=True)

    ok, failed = 0, []
    for idx in range(ROOM_COUNT):
        name = sanitize(room_names[idx], idx)
        try:
            dump_room(rom, ver, idx, name, out_dir)
        except Exception as e:
            print(f"[{idx:02d}] FAILED: {e}", file=sys.stderr)
            failed.append((idx, str(e)))
            continue
        ok += 1
    print(f"{ok}/{ROOM_COUNT} rendered, {len(failed)} failed -> {out_dir}/", file=sys.stderr)
    for idx, err in failed:
        print(f"  room {idx}: {err}", file=sys.stderr)


if __name__ == "__main__":
    main()
