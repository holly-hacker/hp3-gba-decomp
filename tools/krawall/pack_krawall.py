#!/usr/bin/env python3
"""Pack data/audio/ (curated JSON+WAV Krawall content, version-independent)
into per-version, byte-exact assembly for regions.<ver>.txt's
krawall-module/krawall-samples rows. See docs/formats/krawall.md.

Emits real .s text with real labels (mirroring what krawerter's own
outputFile()/Sample::output() would have produced) rather than raw binary
-- so pattern-pointer tables and the sample list resolve through the
normal assembler/linker, and so a module's or sample's symbol
(e.g. `Module0`, `Sample12`) is directly referenceable from other .s files
once matched game code needs to point at it. Byte layout (not text
formatting) is what has to match the original ROM; alignment padding is
computed from absolute addresses in Python rather than trusted to `.align`,
so there's no ambiguity about how many bytes get inserted.

Writes to build/<ver>/audio/ -- gitignored, like the rest of build/.
data/audio/ itself is never touched by this script.

Usage: pack_krawall.py <ver>
"""
import json
import struct
import sys
import wave
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from krawall_codec import compress_pattern, derive_song_index, compute_trailing_buffer

LOOP_MODES = {"none": 0, "forward": 1, "pingpong": 2}


def wav_to_pcm(path: Path) -> bytes:
    with wave.open(str(path), "rb") as w:
        if w.getsampwidth() != 1 or w.getnchannels() != 1:
            sys.exit(f"{path}: expected mono 8-bit WAV")
        frames = w.readframes(w.getnframes())
    # WAV's native 8-bit PCM convention is unsigned, 128=silence -- exactly
    # the ROM's own offset-binary convention (see extract_krawall.py's
    # pcm_to_wav), so the raw bytes come back out as-is, no transform.
    return frames


def parse_krawall_rows(ver: str) -> tuple[list[tuple[int, int, str, str]], tuple[int, int, str, str]]:
    """Returns (module_rows, samples_row) parsed from regions.<ver>.txt."""
    modules = []
    samples_row = None
    with open(f"regions.{ver}.txt") as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] == "krawall-module":
                if len(parts) != 5:
                    sys.exit(f"regions.{ver}.txt:{lineno}: expected 'krawall-module <start> <end> <json> <name>'")
                _, start, end, jsonfile, name = parts
                modules.append((int(start, 16), int(end, 16), jsonfile, name))
            elif parts[0] == "krawall-samples":
                if len(parts) != 5:
                    sys.exit(f"regions.{ver}.txt:{lineno}: expected 'krawall-samples <start> <end> <dir> <name>'")
                if samples_row is not None:
                    sys.exit(f"regions.{ver}.txt:{lineno}: duplicate krawall-samples row")
                _, start, end, samplesdir, name = parts
                samples_row = (int(start, 16), int(end, 16), samplesdir, name)
    if samples_row is None:
        sys.exit(f"regions.{ver}.txt: no krawall-samples row found")
    return modules, samples_row


def emit_bytes(lines: list[str], data: bytes) -> int:
    for i in range(0, len(data), 32):
        lines.append(".byte " + ", ".join(str(b) for b in data[i:i + 32]))
    return len(data)


def emit_pad_to_align4(lines: list[str], cursor: int) -> int:
    pad = (-cursor) % 4
    if pad:
        lines.append(".byte " + ", ".join(["0"] * pad))
    return pad


def resolve_instruments(rows: list[list[dict]], sample_index: dict[str, int]) -> list[list[dict]]:
    resolved = []
    for row in rows:
        new_row = []
        for ev in row:
            new_ev = dict(ev)
            instr = ev.get("instrument")
            if instr is not None:
                if instr not in sample_index:
                    sys.exit(f"unknown sample name {instr!r} referenced by pattern event")
                new_ev["instrument"] = sample_index[instr]
            new_row.append(new_ev)
        resolved.append(new_row)
    return resolved


def pack_module(start_addr: int, end_addr: int, json_path: str, name: str,
                 sample_index: dict[str, int]) -> str:
    module = json.loads(Path(json_path).read_text())
    lines: list[str] = []
    cursor = start_addr

    pattern_labels = []
    for i, pat in enumerate(module["patterns"]):
        resolved_rows = resolve_instruments(pat["rows"], sample_index)
        data, index16 = compress_pattern(resolved_rows)

        pat_label = f"{name}_Pattern{i}"
        pattern_labels.append(pat_label)
        lines.append(f"{pat_label}:")

        idx_bytes = b"".join(struct.pack("<H", v) for v in index16)
        cursor += emit_bytes(lines, idx_bytes)
        cursor += emit_bytes(lines, bytes([len(pat["rows"])]))  # 1-byte rows count (old format)
        cursor += emit_bytes(lines, data)
        cursor += emit_pad_to_align4(lines, cursor)

    lines.append(f"{name}:")

    channels = module["channels"]
    order = module["order"]
    order_bytes = bytes((254 if v is None else v) for v in order)
    if len(order_bytes) > 256:
        sys.exit(f"{name}: order list longer than 256")
    order_bytes = order_bytes + bytes(256 - len(order_bytes))

    channel_pan = module["channelPan"]
    if len(channel_pan) != channels:
        sys.exit(f"{name}: channelPan length ({len(channel_pan)}) != channels ({channels})")
    channel_pan_bytes = bytes((channel_pan[i] if i < channels else 0) & 0xFF for i in range(32))

    song_index = derive_song_index(order)

    header = bytearray()
    header.append(channels)
    header.append(len(order))
    header.append(module["songRestart"])
    header += order_bytes
    header += channel_pan_bytes
    header += bytes(song_index)
    header.append(module["volGlobal"])
    header.append(module["initSpeed"])
    header.append(module["initBPM"])
    header.append(1 if module.get("flagInstrumentBased") else 0)
    header.append(1 if module.get("flagLinearSlides") else 0)
    header.append(1 if module.get("flagFastVolSlides") else 0)
    header += bytes(3)  # always-zero trailing bytes, see docs/formats/krawall.md

    cursor += emit_bytes(lines, bytes(header))

    for lbl in pattern_labels:
        lines.append(f".word {lbl}")
        cursor += 4

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X}")

    return "\n".join(lines) + "\n"


def pack_samples(start_addr: int, end_addr: int, samples_dir: str, name: str) -> tuple[str, dict[str, int]]:
    sdir = Path(samples_dir)
    # Sample order fixes each sample's 1-based instrument index -- the
    # authoritative order is each JSON's own "index" field (written by
    # extract_krawall.py), NOT the filename, since names are user-renamable
    # (see krawall_names.txt) and needn't stay numeric/sorted.
    entries: list[tuple[int, str, dict]] = []
    for p in sdir.glob("*.json"):
        meta = json.loads(p.read_text())
        if "index" not in meta:
            sys.exit(f"{p}: missing required 'index' field")
        entries.append((meta["index"], p.stem, meta))
    entries.sort(key=lambda e: e[0])
    got_indices = [e[0] for e in entries]
    if got_indices != list(range(len(entries))):
        sys.exit(f"sample 'index' fields must be exactly 0..{len(entries)-1} "
                 f"with no gaps/duplicates, got {got_indices}")

    sample_index = {stem: idx + 1 for idx, stem, _ in entries}  # 1-based

    lines: list[str] = []
    cursor = start_addr
    labels = []
    for _, sname, meta in entries:
        pcm = wav_to_pcm(sdir / f"{sname}.wav")

        labels.append(sname)
        lines.append(f"{sname}:")
        lines.append(f".word {meta['loopLength']}")
        cursor += 4
        end_label = f"{sname}_end"
        lines.append(f".word {end_label}")  # size field: address of _end, see docs/formats/krawall.md
        cursor += 4
        lines.append(f".word {meta['c2Freq']}")
        cursor += 4

        loop_mode = LOOP_MODES[meta["loop"]]
        fixed = bytes([
            meta["fineTune"] & 0xFF,
            meta["relativeNote"] & 0xFF,
            meta["volDefault"] & 0xFF,
            meta["panDefault"] & 0xFF,
            loop_mode,
            1 if meta.get("hq") else 0,
        ])
        cursor += emit_bytes(lines, fixed)
        cursor += emit_bytes(lines, pcm)

        lines.append(f"{end_label}:")
        tail = compute_trailing_buffer(pcm, loop_mode, meta["loopLength"])
        cursor += emit_bytes(lines, tail)
        cursor += emit_pad_to_align4(lines, cursor)

    lines.append(f"{name}:")
    for lbl in labels:
        lines.append(f".word {lbl}")
        cursor += 4

    if cursor != end_addr:
        sys.exit(f"{name}: packed size mismatch: got 0x{cursor:X}, "
                  f"regions file declares end 0x{end_addr:X}")

    return "\n".join(lines) + "\n", sample_index


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    module_rows, (s_start, s_end, s_dir, s_name) = parse_krawall_rows(ver)

    out_dir = Path(f"build/{ver}/audio")
    (out_dir / "samples").mkdir(parents=True, exist_ok=True)
    (out_dir / "modules").mkdir(parents=True, exist_ok=True)

    samples_asm, sample_index = pack_samples(s_start, s_end, s_dir, s_name)
    (out_dir / "samples" / f"{s_name}.s").write_text(samples_asm)

    for start, end, json_path, name in module_rows:
        asm = pack_module(start, end, json_path, name, sample_index)
        (out_dir / "modules" / f"{name}.s").write_text(asm)

    print(f"packed {len(module_rows)} modules + samples for {ver}", file=sys.stderr)


if __name__ == "__main__":
    main()
