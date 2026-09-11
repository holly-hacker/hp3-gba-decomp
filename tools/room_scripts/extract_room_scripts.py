#!/usr/bin/env python3
"""One-time bootstrap: disassemble every room's room-script chains (the
bytecode VM documented in docs/formats/room_scripts.md) into curated,
editable text under data/room_scripts/. See extract_battle_scripts.py
for the pattern this mirrors.

Layout: data/room_scripts/<ver>/<roomIdx>_<RoomName>/chain<N>.txt (or a
curated name from script_names.json), plus that room directory's own
index.json (a JSON array of filenames, position = chain index) --
mirrors data/battle_scripts/index.json's role, so a chain's file can be
renamed via script_names.json without disturbing chain order. Room
names are resolved from the dialog string table (see
docs/formats/levels.md's "Room names, PROVEN").

Unlike tools/battle_scripts/'s extract/pack pair, pack_room_scripts.py
does not (yet) emit build assembly -- the room table at 0x08063C8C
isn't a regions.<ver>.txt region yet (see docs/formats/levels.md's "Not
yet located"), so there's nowhere in the real build for a chain to be
packed back into. pack_room_scripts.py instead re-encodes data/ and
verifies it reproduces the baserom's bytes exactly, the same codec
round-trip a real pack step would rely on later.

data/room_scripts/ is gitignored, same footing as the baserom (hard
rule 2, AGENTS.md) -- every clone needs to run this once (see the
`extract-room-scripts` recipe). Clears every room directory first, so a
chain whose name changes (via script_names.json) doesn't leave its old
filename behind as a stale orphan; do not run it against already
hand-edited content.

Only each room's quest-stage-0 (story-start) variant sub-block is
extracted -- a room's resource blob carries a separate switch-state
chain set per quest stage, selected at runtime by
`g_abQuestEventState[0]` (see docs/formats/rooms.md's room-resource-blob
section); extracting every stage's variant is further work, not done
here.

US only -- the level table's JP-ROM address isn't located yet (see
docs/formats/levels.md).

Usage: extract_room_scripts.py <ver>   (writes data/room_scripts/<ver>/)
"""
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent.parent / "text"))
from room_scripts_codec import (
    decode_chain,
    format_chain_text,
    script_key,
    NAME_RE,
    SCRIPT_DESCRIPTION_BY_KEY,
    SCRIPT_NAME_BY_KEY,
)
from decode_dialog_text import decode_dialog_text

ROM_BASE = 0x08000000
ROOM_TABLE_ADDR = {"us": 0x08063C8C}
ROOM_TABLE_STRIDE = 0x7C
ROOM_COUNT = 55
ROOM_RESOURCE_BLOB_OFFSET = 0x50
ROOM_NAME_STRING_ID_BASE = 0x54A

# ShowRoomDialog's operand is NOT a GetDialogText string id directly -- it
# indexes this 8-byte-stride table (found by tracing DAT_03002e94 from
# FUN_0801fb54 into the Dialogue game mode's per-line tick, FUN_0801f96c):
# entry = {u32 linesPtr, u32 lineCount}; linesPtr[i] (u32, i in
# 0..lineCount-1) is the real GetDialogText id for that block's i-th line.
# FUN_0801fc28 (called per line from FUN_0801f96c) confirms this: it calls
# GetDialogText(param_1) where param_1 is exactly one of these linesPtr[i]
# values, not the raw ShowRoomDialog operand. See docs/formats/room_scripts.md.
DIALOG_BLOCK_TABLE_ADDR = 0x0805CB50


def u8(rom, addr):
    return rom[addr - ROM_BASE]


def u16(rom, addr):
    return struct.unpack_from("<H", rom, addr - ROM_BASE)[0]


def u32(rom, addr):
    return struct.unpack_from("<I", rom, addr - ROM_BASE)[0]


def sanitize(name, idx):
    s = re.sub(r"[^A-Za-z0-9]+", "_", name).strip("_")
    return f"{idx:02d}_{s or 'room'}"


def switch_state_chains(rom, blob_addr, quest_stage=0):
    """Returns a list of raw chain byte-strings for a room's
    quest-stage-selected sub-block, per ParseRoomResourceBlob_candidate/
    BuildRoomSwitchStateObjectTable_candidate (see docs/formats/room_scripts.md
    and docs/formats/rooms.md's room-resource-blob section):

      pSub = blob + u16(blob+0)
      variant index N = u8(pSub + 1 + questStage)
      sub-block = blob + u16(pSub + N*8 + 0x24)
      switch-state sub-table = subBlock + u16(subBlock+2)
      count = u8(subTable+0)
      chain[i] = subTable + u16(subTable + 2 + i*2)

    quest_stage=0 (g_abQuestEventState[0]'s value at a fresh game) picks
    the story-start variant; other quest stages select a different set of
    chains for the same room (not extracted here -- see this file's
    docstring)."""
    p_sub = blob_addr + u16(rom, blob_addr)
    variant_index = u8(rom, p_sub + 1 + quest_stage)
    sub_block = blob_addr + u16(rom, p_sub + variant_index * 8 + 0x24)
    sub_table = sub_block + u16(rom, sub_block + 2)
    count = u8(rom, sub_table)
    chains = []
    for i in range(count):
        chain_start = sub_table + u16(rom, sub_table + 2 + i * 2)
        # Chains are packed back-to-back with no length prefix; walk the
        # opcode-length table (via decode_chain) to find where this one ends.
        raw = rom[chain_start - ROM_BASE: chain_start - ROM_BASE + 0x4000]
        instructions = decode_chain(raw)
        end = sum(4 + len(operands) for _, operands in instructions)
        chains.append(raw[:end])
    return chains


def dialog_block_line_ids(rom, block_id):
    """Resolves a ShowRoomDialog operand (a block id) to the list of real
    GetDialogText string ids it plays, in order -- see
    DIALOG_BLOCK_TABLE_ADDR's comment above."""
    entry_addr = DIALOG_BLOCK_TABLE_ADDR + block_id * 8
    lines_ptr = u32(rom, entry_addr)
    line_count = u32(rom, entry_addr + 4)
    return [u32(rom, lines_ptr + i * 4) for i in range(line_count)]


def render_dialog_text(text: bytes) -> str:
    # Values 0xF0-0xFF start an undecoded extended glyph escape (see
    # decode_dialog_text.py); render those as \xNN, everything else as its
    # raw byte (ASCII/Latin-1-ish for English).
    out = []
    for b in text.rstrip(b"\x00"):
        out.append(chr(b) if b <= 0xEF else f"\\x{b:02x}")
    return "".join(out)


def make_dialog_resolver(rom):
    def resolve(source, values):
        if source["type"] != "dialog_text":
            return None
        block_id = values[source["value_index"]]
        try:
            line_ids = dialog_block_line_ids(rom, block_id)
            lines = [render_dialog_text(decode_dialog_text(rom, 0, sid)) for sid in line_ids]
        except Exception as e:
            return [f"<dialog block {block_id} decode failed: {e}>"]
        return [f'"{line}"' for line in lines]
    return resolve


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    if ver not in ROOM_TABLE_ADDR:
        sys.exit(f"room table address not yet confirmed for ver={ver!r} (US only so far)")

    rom = Path(f"baserom.{ver}.gba").read_bytes()
    resolve_comment = make_dialog_resolver(rom)

    try:
        room_names = [decode_dialog_text(rom, 0, ROOM_NAME_STRING_ID_BASE + i).rstrip(b"\x00").decode("latin-1", "replace")
                      for i in range(ROOM_COUNT)]
    except Exception as e:
        print(f"room-name decode failed, using room<N>: {e}", file=sys.stderr)
        room_names = [f"room{i}" for i in range(ROOM_COUNT)]

    out_root = Path("data/room_scripts") / ver
    out_root.mkdir(parents=True, exist_ok=True)
    for stale in out_root.glob("*"):
        if stale.is_dir():
            for f in stale.glob("*"):
                f.unlink()
            stale.rmdir()

    total_chains, failed = 0, []
    for idx in range(ROOM_COUNT):
        room_label = sanitize(room_names[idx], idx)
        room_dir = out_root / room_label
        blob_addr = u32(rom, ROOM_TABLE_ADDR[ver] + idx * ROOM_TABLE_STRIDE + ROOM_RESOURCE_BLOB_OFFSET)
        try:
            chains = switch_state_chains(rom, blob_addr)
        except Exception as e:
            print(f"[{idx:02d}] {room_label}: FAILED: {e}", file=sys.stderr)
            failed.append((idx, str(e)))
            continue

        room_dir.mkdir(parents=True, exist_ok=True)
        filenames = []
        for chain_idx, raw in enumerate(chains):
            key = script_key(idx, chain_idx)
            curated_name = SCRIPT_NAME_BY_KEY.get(key)
            if curated_name is not None and not NAME_RE.match(curated_name):
                sys.exit(f"script_names.json: {key!r} name {curated_name!r} isn't a valid "
                          "filename stem (letters/digits/underscore, not starting with a digit)")
            filename = f"{curated_name if curated_name else f'chain{chain_idx}'}.txt"
            instructions = decode_chain(raw)
            text = format_chain_text(instructions, resolve_comment, SCRIPT_DESCRIPTION_BY_KEY.get(key))
            (room_dir / filename).write_text(text)
            filenames.append(filename)
        (room_dir / "index.json").write_text(json.dumps(filenames, indent=2) + "\n")
        total_chains += len(chains)

    print(f"{ROOM_COUNT - len(failed)}/{ROOM_COUNT} rooms, {total_chains} chains -> {out_root}/", file=sys.stderr)
    for idx, err in failed:
        print(f"  room {idx}: {err}", file=sys.stderr)


if __name__ == "__main__":
    main()
