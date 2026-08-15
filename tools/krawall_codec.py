#!/usr/bin/env python3
"""Shared encode/decode helpers for Krawall pattern-row compression, the
module-header songIndex derivation, and sample trailing-buffer generation.

Used by both tools/krawall_migrate.py (ROM -> data/audio/ JSON+WAV,
one-time bootstrap) and tools/pack_krawall.py (data/audio/ -> per-version
assembly at build time). All formats here are confirmed against this
game's actual embedded Krawall revision (2003-09-01) -- see
docs/formats/krawall.md's "Pattern atom encoding" and "Module header
fields" sections for the verification behind each of these, including
where it disagrees with the current public krawall repo's active (later
revision) code paths.

Also holds krawall_names.txt loading/resolution (module/sample naming),
shared by tools/krawall_migrate.py and tools/gen_krawall_regions.py so
both agree on the same name for a given index.
"""
import re
import sys
from pathlib import Path

NOTE_OFF = 127

# A name becomes a real assembler label (pack_krawall.py emits it as
# `<name>:`) sharing one flat symbol namespace with the rest of the
# assembled ROM, so it must be a valid, unambiguous identifier.
NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def load_krawall_names(path: str = "krawall_names.txt") -> tuple[dict[int, str], dict[int, str]]:
    """Parse krawall_names.txt: '<module|sample> <index> <Name>' lines,
    '#'-comments and blank lines skipped. Returns (module_names,
    sample_names), each {index: Name}. Not every index needs an entry --
    unmapped ones fall back to Module<N>/Sample<N>, see resolve_names.
    Missing file is not an error (nothing named yet)."""
    module_names: dict[int, str] = {}
    sample_names: dict[int, str] = {}
    if not Path(path).exists():
        return module_names, sample_names
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if len(parts) != 3:
                sys.exit(f"{path}:{lineno}: expected '<module|sample> <index> <Name>'")
            kind, idx_s, name = parts
            if kind not in ("module", "sample"):
                sys.exit(f"{path}:{lineno}: kind must be 'module' or 'sample', got {kind!r}")
            if not idx_s.isdigit():
                sys.exit(f"{path}:{lineno}: index must be a non-negative integer")
            if not NAME_RE.match(name):
                sys.exit(f"{path}:{lineno}: name {name!r} must be a valid identifier "
                          "(it becomes an assembly label) -- letters/digits/underscore, "
                          "not starting with a digit")
            idx = int(idx_s)
            target = module_names if kind == "module" else sample_names
            if idx in target:
                sys.exit(f"{path}:{lineno}: duplicate {kind} entry for index {idx}")
            if name in target.values():
                sys.exit(f"{path}:{lineno}: name {name!r} already used for another {kind}")
            target[idx] = name
    return module_names, sample_names


def resolve_names(kind: str, count: int, names: dict[int, str]) -> list[str]:
    """Returns count names, index i named names.get(i, f"{Kind}{i}").
    Exits if any two indices resolve to the same name (a custom name
    colliding with another custom name, or with an unmapped index's
    default Module<N>/Sample<N>)."""
    default_prefix = kind.capitalize()
    resolved = [names.get(i, f"{default_prefix}{i}") for i in range(count)]
    seen: dict[str, int] = {}
    for i, name in enumerate(resolved):
        if name in seen:
            sys.exit(f"name collision: {kind} {seen[name]} and {kind} {i} "
                      f"both resolve to {name!r}")
        seen[name] = i
    return resolved

# krawerter's Sample.cpp: fixed-size mixer overrun buffer appended after
# every sample's real PCM data. See docs/formats/krawall.md's Trailing
# padding absorption.
SAMPLES_ADD = 17 * 4 + 1


def align4(addr: int) -> int:
    return (addr + 3) & ~3


def decompress_pattern(data: bytes, rows: int) -> list[list[dict]]:
    """Parse a pattern's compressed row stream (starting right after the
    rows-count byte) into rows of sparse channel events. Field values are
    decoded per docs/formats/krawall.md's Pattern atom encoding (packed
    16-bit note/instrument word, our confirmed revision only -- NOT the
    current public krawall repo's active byte-per-field encoding)."""
    out: list[list[dict]] = []
    pos = 0
    for _ in range(rows):
        row: list[dict] = []
        while True:
            follow = data[pos]
            pos += 1
            if not follow:
                break
            event: dict = {"channel": follow & 0x1F}
            if follow & 0x20:
                b1, b2 = data[pos], data[pos + 1]
                pos += 2
                word = (b1 << 8) | b2
                note = word >> 9
                instrument = word & 0x1FF
                if note == NOTE_OFF:
                    event["note"] = "off"
                elif note:
                    event["note"] = note
                if instrument:
                    event["instrument"] = instrument
            if follow & 0x40:
                event["volume"] = data[pos]
                pos += 1
            if follow & 0x80:
                event["effect"] = data[pos]
                event["effectop"] = data[pos + 1]
                pos += 2
            row.append(event)
        out.append(row)
    return out


def compress_pattern(rows: list[list[dict]]) -> tuple[bytes, list[int]]:
    """Inverse of decompress_pattern. `instrument`, when present, must
    already be resolved to a plain 1-based numeric sample index (not a
    name) -- see pack_krawall.py's instrument-name resolution step.
    Returns (data_bytes, index16) where index16[n] is the byte offset of
    row 4*n within data_bytes, for rows 0, 4, 8, ... 60."""
    out = bytearray()
    index16 = [0] * 16
    for r, row in enumerate(rows):
        if r % 4 == 0 and r // 4 < 16:
            index16[r // 4] = len(out)
        for event in row:
            channel = event["channel"]
            note = event.get("note")
            note_val = NOTE_OFF if note == "off" else (note or 0)
            instrument = event.get("instrument", 0) or 0
            volume = event.get("volume")
            effect = event.get("effect")
            effectop = event.get("effectop")

            has_ni = bool(note_val) or bool(instrument)
            has_vol = volume is not None
            has_fx = (effect is not None) or (effectop is not None)

            follow = channel & 0x1F
            if has_ni:
                follow |= 0x20
            if has_vol:
                follow |= 0x40
            if has_fx:
                follow |= 0x80
            out.append(follow)

            if has_ni:
                word = ((note_val & 0x7F) << 9) | (instrument & 0x1FF)
                out.append((word >> 8) & 0xFF)
                out.append(word & 0xFF)
            if has_vol:
                out.append(volume & 0xFF)
            if has_fx:
                out.append((effect or 0) & 0xFF)
                out.append((effectop or 0) & 0xFF)
        out.append(0)
    return bytes(out), index16


def derive_song_index(order: list) -> list[int]:
    """Port of Mod.cpp::outputFile()'s songIndex derivation -- see
    docs/formats/krawall.md's Module header fields. `order` entries are
    `None` for the 254 skip marker, else a pattern index."""
    song_index = [0] * 64
    idx = 1
    seen_marker = False
    for i, v in enumerate(order):
        if v is None:
            seen_marker = True
        else:
            if seen_marker:
                if idx < 64:
                    song_index[idx] = i
                idx += 1
                seen_marker = False
    return song_index


def compute_trailing_buffer(pcm: bytes, loop_mode: int, loop_length: int) -> bytes:
    """Port of Sample.cpp::output()'s SAMPLES_ADD-byte overrun buffer.
    loop_mode: 0 = none, 1 = forward, 2 = ping-pong."""
    length = len(pcm)
    if loop_mode == 0:
        return bytes([0x80]) * SAMPLES_ADD
    if loop_mode == 1:
        loop_begin = length - loop_length
        return bytes(pcm[loop_begin + sz] for sz in range(SAMPLES_ADD))
    if loop_mode == 2:
        return bytes(pcm[length - 1 - sz] for sz in range(SAMPLES_ADD))
    raise ValueError(f"invalid loop_mode {loop_mode}")
