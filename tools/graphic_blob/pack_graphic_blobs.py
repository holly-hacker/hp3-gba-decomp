#!/usr/bin/env python3
"""Pack every graphic-blobs manifest row from data/graphic_blobs/.

A row `graphic-blobs <start> <end> <dir> <name>` claims a run of contiguous
graphic blobs (see blobs.py). <dir>/bank.json lists them in ROM order, each
with its flags and the images it is built from. The packed blobs, and the
assembly that labels each as g<BlobName> (or its `symbol`), go under build/<ver>/graphic_blobs/;
the C declarations go to include/gen/<name>.h.

A blob without a palette may name `palette`, the blob or label whose colors its
PNG shows; the packer does not use it.
A blob whose tiles and tilemap the standard rebuild (see blobs.py) does not
reproduce lists its tilemap cells' tiles and flips as `layout`.

Usage: pack_graphic_blobs.py <ver>
"""
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import stamp

ROOT = Path(__file__).resolve().parents[2]
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "flags"}
OPTIONAL_ENTRY_KEYS = {"highBits", "unused", "symbol", "palette", "layout"}


def graphic_blob_rows(ver: str):
    path = ROOT / f"regions.{ver}.txt"
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        parts = raw.split("#", 1)[0].split()
        if not parts or parts[0] != "graphic-blobs":
            continue
        if len(parts) != 5:
            raise SystemExit(f"{path}:{lineno}: expected graphic-blobs <start> <end> <dir> <name>")
        _, start, end, source, name = parts
        if not SYMBOL.fullmatch(name):
            raise SystemExit(f"{path}:{lineno}: invalid bank name {name!r}")
        yield int(start, 16), int(end, 16), ROOT / source, name


def manifest_labels(ver: str) -> dict[int, str]:
    """Address to symbol for the `label` rows of regions.<ver>.txt."""
    labels = {}
    for raw in (ROOT / f"regions.{ver}.txt").read_text().splitlines():
        parts = raw.split("#", 1)[0].split()
        if len(parts) == 3 and parts[0] == "label":
            labels[int(parts[1], 16)] = parts[2]
    return labels


def load_index(source: Path) -> list[dict]:
    path = source / "bank.json"
    index = json.loads(path.read_text())
    if set(index) != {"format", "blobs"} or index["format"] != 1:
        raise ValueError(f"{path}: expected format 1 with blobs")
    names = set()
    for entry in index["blobs"]:
        if not ENTRY_KEYS <= set(entry) <= ENTRY_KEYS | OPTIONAL_ENTRY_KEYS:
            raise ValueError(f"{path}: {entry.get('name')}: unrecognized set of keys")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"{path}: invalid or duplicate blob name {name!r}")
        names.add(name)
        flags = entry["flags"]
        if not (isinstance(flags, list) and len(flags) == 2 and all(isinstance(f, int) and 0 <= f < 256 for f in flags)):
            raise ValueError(f"{path}: {name}: flags must be two bytes")
        blobs.check_flags(*flags)
        for key in OPTIONAL_ENTRY_KEYS & set(entry):
            value = entry[key]
            if key in ("symbol", "palette"):
                ok = isinstance(value, str) and SYMBOL.fullmatch(value)
            elif key == "layout":
                ok = isinstance(value, list) and all(isinstance(i, int) and 0 <= i < 0x1000 for i in value)
            elif key == "unused":
                ok = isinstance(value, int) and value > 0
            else:
                ok = isinstance(value, list) and all(isinstance(i, int) and 0 <= i < 256 for i in value)
            if not ok:
                raise ValueError(f"{path}: {name}: invalid {key}")
    files = {f"{e['name']}.png" for e in index["blobs"]}
    files |= {f"{e['name']}.unused.png" for e in index["blobs"] if e.get("unused")}
    extras = {p.name for p in source.glob("*.png")} - files
    if extras:
        raise ValueError(f"{path}: unlisted PNG files: {', '.join(sorted(extras))}")
    return index["blobs"]


def blob_from_files(source: Path, entry: dict) -> blobs.Blob:
    size, pixels, colors = blobs.read_png(source / f"{entry['name']}.png")
    if size[0] % 8 or size[1] % 8:
        raise ValueError(f"{entry['name']}.png: {size[0]}x{size[1]} is not a multiple of 8 pixels")
    unused = []
    if entry.get("unused"):
        _, sheet, _ = blobs.read_png(source / f"{entry['name']}.unused.png")
        unused = blobs.unused_from_sheet(sheet, entry["unused"])
    flags0 = entry["flags"][0]
    palette = blobs.encode_palette(colors, entry.get("highBits", [])) if flags0 & 1 else None
    return blobs.blob_from_image(*entry["flags"], palette, size[0] // 8, size[1] // 8, pixels, unused,
                                   entry.get("layout"))


def _build(args) -> bytes:
    source, entry = args
    return blobs.build(blob_from_files(source, entry))


def pack_bank(ver: str, start: int, end: int, source: Path, name: str) -> int:
    entries = load_index(source)
    out = ROOT / "build" / ver / "graphic_blobs"
    out.mkdir(parents=True, exist_ok=True)
    header_path = ROOT / f"include/gen/{name}.h"
    if stamp.fresh(out / f"{name}.s", source, ROOT / f"regions.{ver}.txt"):
        return len(entries)
    from concurrent.futures import ProcessPoolExecutor
    with ProcessPoolExecutor() as pool:
        packed = list(pool.map(_build, [(source, e) for e in entries]))
    size = sum(map(len, packed))
    if size != end - start:
        raise ValueError(f"{name}: packs to {size:#x} bytes, the manifest claims {end - start:#x}")
    (out / f"{name}.bin").write_bytes(b"".join(packed))
    asm, header, offset = [], ["// Generated by tools/graphic_blob/pack_graphic_blobs.py; do not edit.",
                               "#pragma once", "", '#include "types.h"', ""], 0
    for entry, data in zip(entries, packed):
        label = entry.get("symbol", f"g{entry['name']}")
        asm += [f".global {label}", f"{label}:",
                f'    .incbin "build/{ver}/graphic_blobs/{name}.bin", {offset}, {len(data)}']
        header.append(f"extern const u8 {label}[];")
        offset += len(data)
    (out / f"{name}.s").write_text("\n".join(asm) + "\n")
    header_text = "\n".join(header) + "\n"
    if not header_path.is_file() or header_path.read_text() != header_text:
        header_path.write_text(header_text)
    return len(entries)


def main() -> None:
    ver = sys.argv[1] if len(sys.argv) > 1 else "us"
    try:
        for start, end, source, name in graphic_blob_rows(ver):
            print(f"{ver}: packed {name}: {pack_bank(ver, start, end, source, name)} blobs, {end - start} bytes")
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
