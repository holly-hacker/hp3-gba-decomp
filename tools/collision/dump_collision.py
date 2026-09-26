#!/usr/bin/env python3
"""Render every room's collision map (walkability + tile-type + layer
data) as PNGs for visual inspection against real gameplay. See
docs/formats/collision.md for the format this decodes and what every
tile type/layer value means (code-confirmed vs. user-verified in-game).

Research/debugging aid only -- NOT build input. Collision data isn't
proven complete enough for a regions.<ver>.txt row yet (several field
offsets and the room-25/room-29 slope-orientation discrepancy are still
open, see collision.md's "Not yet located"), so there is no pack step:
this only ever reads the baserom and writes to extracted/, mirroring
dump_krawall.py's role for Krawall.

US only -- the level table's JP-ROM address isn't located yet (see
docs/formats/levels.md).

Usage: dump_collision.py <ver>   (writes extracted/collision/<ver>/)
"""
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent / "graphics"))
sys.path.insert(0, str(Path(__file__).parent.parent / "text"))
from decode_gamma_lz import decode_gamma_lz, CODEC_ADDR, _apply_delta_pass
from decode_bios import DECODERS
from decode_dialog_text import decode_dialog_text

import numpy as np
from PIL import Image, ImageDraw

ROM_BASE = 0x08000000
TABLE_BASE = {"us": 0x08063C8C}
STRIDE = 0x7C
ROOM_COUNT = 55
UPSCALE = 3

# Only types 1-25 actually block movement (FUN_0802DA20); 0x1F/0x29 are
# force-blocked conditionally by ApplyTileCollisionEffect_candidate;
# everything else 26+ is passable terrain with a side effect, not a wall.
# See docs/formats/collision.md.
CONDITIONAL_BLOCK_TYPES = {0x1F, 0x29}
KNOWN_EFFECT_NAMES = {
    0x1F: "Lumos crossing (user-verified) / conditional block",
    0x22: "unwalkable water (user-verified) / force-blocks wObjectType==0",
    0x23: "switch-state toggle A",
    0x24: "switch-state toggle B",
    0x29: "blocks all but wObjectType==0xF",
    0x2D: "ice, Glacius puzzle surface (user-verified)",
    0x1B: "stairs, horizontal, bottom-left/top-right (user-verified)",
    0x1C: "stairs, horizontal, bottom-right/top-left (user-verified)",
    0x1E: "stairs, vertical, bottom-at-bottom (user-verified)",
    0x25: "stairs, diagonal, bottom-left to top-right (user-verified)",
    0x27: "stairs, diagonal (user-verified, tentative orientation)",
    0x28: "stairs, diagonal, bottom-right to top-left (user-verified)",
    0x2B: "stairs, repairable by Reparo (user-verified)",
}

BASE_COLORS = [
    (230, 25, 75), (60, 180, 75), (0, 130, 200), (245, 130, 48),
    (145, 30, 180), (70, 240, 240), (240, 50, 230), (210, 245, 60),
    (250, 190, 212), (0, 128, 128), (220, 190, 255), (170, 110, 40),
    (255, 250, 200), (128, 0, 0), (170, 255, 195), (128, 128, 0),
    (255, 215, 180), (0, 0, 128), (255, 225, 25), (255, 105, 180),
    (75, 0, 130), (154, 205, 50), (0, 100, 0), (139, 69, 19),
]
HATCH_PATTERNS = ["diag1", "diag2", "horiz", "vert", "dots", "cross", "checker", "thickdiag"]
LAYER_MARK_COLORS = {1: (30, 90, 255), 2: (30, 200, 60), 3: (230, 200, 20)}


def u32(rom, addr):
    return struct.unpack_from("<I", rom, addr - ROM_BASE)[0]


def decode_resource(rom, addr):
    off = addr - ROM_BASE
    b0 = rom[off]
    typ = (b0 >> 4) & 7
    extra_pass = bool(b0 & 0x80)
    if typ == 6:
        return decode_gamma_lz(rom, addr, CODEC_ADDR["us"])
    if typ in (1, 2, 3):
        out = DECODERS[typ](rom, addr)
    elif typ == 0:
        size = rom[off + 1] | (rom[off + 2] << 8) | (rom[off + 3] << 16)
        out = rom[off + 4:off + 4 + size]
    else:
        raise ValueError(f"unhandled codec type {typ} at {addr:#010x}")
    return _apply_delta_pass(out) if extra_pass else out


def load_slopes(rom):
    raw = rom[0x080660A4 - ROM_BASE: 0x080660A4 - ROM_BASE + 24 * 2]
    return [(raw[i * 2] & 0xF, raw[i * 2] >> 4, raw[i * 2 + 1] & 0xF, raw[i * 2 + 1] >> 4) for i in range(24)]


def sanitize(name, idx):
    s = re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_")
    return f"{idx:02d}_{s or 'room'}"


def type_style(t):
    i = t - 26
    return BASE_COLORS[i % len(BASE_COLORS)], HATCH_PATTERNS[i % len(HATCH_PATTERNS)]


def hatch_hit(lx, ly, pattern):
    return {
        "diag1": (lx + ly) % 4 == 0,
        "diag2": (lx - ly) % 4 == 0,
        "horiz": ly % 3 == 1,
        "vert": lx % 3 == 1,
        "dots": (lx % 3 == 1) and (ly % 3 == 1),
        "cross": (lx == 3 or lx == 4 or ly == 3 or ly == 4),
        "checker": ((lx // 2) + (ly // 2)) % 2 == 0,
        "thickdiag": (lx + ly) % 4 in (0, 1),
    }[pattern]


def paint_hatch(out_rgb, py0, px0, color, pattern):
    for ly in range(8):
        for lx in range(8):
            if hatch_hit(lx, ly, pattern):
                out_rgb[py0 + ly, px0 + lx] = color


def render_room(rom, ver, idx, slopes):
    base = TABLE_BASE[ver] + idx * STRIDE
    bg0 = decode_resource(rom, u32(rom, base + 0x00))
    behavior = decode_resource(rom, u32(rom, base + 0x40))
    tilemap = decode_resource(rom, u32(rom, base + 0x44))

    width_blocks, height_blocks = bg0[0], bg0[2]
    if width_blocks == 0 or height_blocks == 0:
        raise ValueError(f"degenerate room size {width_blocks}x{height_blocks}")
    width_px, height_px = width_blocks << 5, height_blocks << 5

    needed = width_blocks * height_blocks * 2
    grid_bytes = tilemap[4:4 + needed]
    if len(grid_bytes) < needed:
        raise ValueError(f"tilemap too short: {len(grid_bytes)} < {needed}")
    grid = np.frombuffer(grid_bytes, dtype="<u2").reshape((height_blocks, width_blocks))
    behavior_arr = np.frombuffer(behavior, dtype=np.uint8)
    max_pattern = len(behavior_arr) // 16

    bw = np.zeros((height_px, width_px, 3), dtype=np.uint8)
    annot = np.zeros((height_px, width_px, 3), dtype=np.uint8)
    seen_special = set()

    for by in range(height_blocks):
        row = grid[by]
        for bx in range(width_blocks):
            pattern_id = int(row[bx]) & 0xFFF
            if pattern_id >= max_pattern:
                pattern_id = 0
            cell = behavior_arr[pattern_id * 16: pattern_id * 16 + 16]
            px0b, py0b = bx * 32, by * 32
            for celly in range(4):
                for cellx in range(4):
                    sub_index = (cellx & 3) | ((celly & 3) << 2)
                    raw_byte = int(cell[sub_index])
                    tile_type = raw_byte & 0x3F
                    layer = raw_byte >> 6
                    px0, py0 = px0b + cellx * 8, py0b + celly * 8

                    if tile_type == 0:
                        bw[py0:py0 + 8, px0:px0 + 8] = 255
                        annot[py0:py0 + 8, px0:px0 + 8] = 255
                    elif tile_type == 1:
                        bw[py0:py0 + 8, px0:px0 + 8] = 0
                        annot[py0:py0 + 8, px0:px0 + 8] = 0
                    elif 2 <= tile_type <= 25:
                        x0, y0, x1, y1 = slopes[tile_type - 2]
                        for ly in range(8):
                            for lx in range(8):
                                cross = (ly - y0) * (x1 - x0) - (y1 - y0) * (lx - x0)
                                c = 255 if cross < 0 else 0
                                bw[py0 + ly, px0 + lx] = c
                                annot[py0 + ly, px0 + lx] = c
                    elif tile_type in CONDITIONAL_BLOCK_TYPES:
                        seen_special.add(tile_type)
                        bw[py0:py0 + 8, px0:px0 + 8] = 255
                        for ly in range(0, 8, 2):
                            for lx in range(8):
                                if (lx + ly) % 4 == 0:
                                    bw[py0 + ly, px0 + lx] = 140
                        annot[py0:py0 + 8, px0:px0 + 8] = 255
                        color, pattern = type_style(tile_type)
                        paint_hatch(annot, py0, px0, color, pattern)
                    else:
                        seen_special.add(tile_type)
                        bw[py0:py0 + 8, px0:px0 + 8] = 255
                        annot[py0:py0 + 8, px0:px0 + 8] = 255
                        color, pattern = type_style(tile_type)
                        paint_hatch(annot, py0, px0, color, pattern)

                    if layer in LAYER_MARK_COLORS:
                        # Small filled corner block, not a full row/column
                        # outline -- an outline draws a visible grid over
                        # any region where most tiles share a layer value.
                        # Unrelated to the slope-orientation bug in
                        # collision.md; that's real regardless of marker
                        # style.
                        annot[py0:py0 + 2, px0:px0 + 2] = LAYER_MARK_COLORS[layer]

    return bw, annot, seen_special


def upscale(arr):
    return np.kron(arr, np.ones((UPSCALE, UPSCALE, 1), dtype=arr.dtype))


def paint_hatch_scaled(box, color, pattern):
    h, w, _ = box.shape
    for ly in range(h):
        for lx in range(w):
            if hatch_hit(lx * 8 // w, ly * 8 // h, pattern):
                box[ly, lx] = color


def write_legend(out_dir, all_special):
    entries = [("open (passable)", (255, 255, 255), None),
               ("solid (type 1 / slope solid side)", (0, 0, 0), None),
               ("conditional block (0x1F/0x29, game-state dependent)", (140, 140, 140), None)]
    for lv, c in LAYER_MARK_COLORS.items():
        entries.append((f"layer={lv} corner mark (top 2 bits of byte; "
                         f"1=occlusion confirmed, 2/3 unconfirmed)", c, None))
    for t in sorted(all_special):
        color, pattern = type_style(t)
        label = f"type {t:#04x} ({t})"
        label += f" -- {KNOWN_EFFECT_NAMES[t]}" if t in KNOWN_EFFECT_NAMES else " -- UNKNOWN, walkable"
        entries.append((label, color, pattern))

    sw = 36
    leg = Image.new("RGB", (620, sw * len(entries) + 10), (30, 30, 30))
    d = ImageDraw.Draw(leg)
    y = 5
    for label, color, pattern in entries:
        box = np.full((sw - 6, sw - 6, 3), 255, dtype=np.uint8)
        if pattern:
            paint_hatch_scaled(box, color, pattern)
        elif color != (255, 255, 255):
            box[:, :] = color
        leg.paste(Image.fromarray(box, "RGB"), (5, y))
        d.rectangle([5, y, sw - 1, y + sw - 6], outline=(200, 200, 200))
        d.text((sw + 8, y + 8), label, fill=(255, 255, 255))
        y += sw
    leg.save(f"{out_dir}/TYPE_LEGEND.png")


def main():
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    if ver not in TABLE_BASE:
        sys.exit(f"room table address not yet confirmed for ver={ver!r} (US only so far)")

    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    slopes = load_slopes(rom)

    try:
        room_names = [decode_dialog_text(rom, 0, 0x54A + i).rstrip(b"\x00").decode("latin-1", "replace")
                      for i in range(ROOM_COUNT)]
    except Exception as e:
        print(f"room-name decode failed, using room<N>: {e}", file=sys.stderr)
        room_names = [f"room{i}" for i in range(ROOM_COUNT)]

    out_dir = Path("extracted/collision") / ver
    out_dir.mkdir(parents=True, exist_ok=True)

    all_special = set()
    ok, failed = 0, []
    for idx in range(ROOM_COUNT):
        name = sanitize(room_names[idx], idx)
        try:
            bw, annot, seen = render_room(rom, ver, idx, slopes)
        except Exception as e:
            print(f"[{idx:02d}] FAILED: {e}", file=sys.stderr)
            failed.append((idx, str(e)))
            continue
        all_special |= seen
        Image.fromarray(upscale(bw), "RGB").save(out_dir / f"collision_bw_{name}.png")
        Image.fromarray(upscale(annot), "RGB").save(out_dir / f"collision_annot_{name}.png")
        ok += 1
    write_legend(out_dir, all_special)
    print(f"{ok}/{ROOM_COUNT} rendered, {len(failed)} failed -> {out_dir}/", file=sys.stderr)
    for idx, err in failed:
        print(f"  room {idx}: {err}", file=sys.stderr)


if __name__ == "__main__":
    main()
