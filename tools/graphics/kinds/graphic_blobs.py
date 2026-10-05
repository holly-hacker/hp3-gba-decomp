"""graphic-blobs runs: graphic blobs (see tools/graphic_blob/blobs.py).

Settings: the ordered `blobs` list, each with its flags and the images it is
built from. Each blob is labeled g<Name>, or its `symbol`. A blob without a
palette may name `palette`, the blob or label whose colors its PNG shows;
packing does not use it. A blob whose tiles and tilemap the standard rebuild
does not reproduce lists its tilemap cells' tiles and flips as `layout`. See
docs/formats/graphic_blob.md.
"""
import re
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

import blobs

ROOT = Path(__file__).resolve().parents[3]
ROM_BASE = blobs.ROM_BASE
ITEMS = "blobs"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
ENTRY_KEYS = {"name", "flags"}
OPTIONAL_ENTRY_KEYS = {"highBits", "unused", "symbol", "palette", "layout"}


def check(run: dict) -> None:
    if set(run) != {"blobs"}:
        raise ValueError("expected blobs")
    names = set()
    for entry in run["blobs"]:
        if not ENTRY_KEYS <= set(entry) <= ENTRY_KEYS | OPTIONAL_ENTRY_KEYS:
            raise ValueError(f"{entry.get('name')}: unrecognized set of keys")
        name = entry["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate blob name {name!r}")
        names.add(name)
        flags = entry["flags"]
        if not (isinstance(flags, list) and len(flags) == 2 and all(isinstance(f, int) and 0 <= f < 256 for f in flags)):
            raise ValueError(f"{name}: flags must be two bytes")
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
                raise ValueError(f"{name}: invalid {key}")


def item_files(run: dict, entry: dict) -> list[str]:
    return [f"{entry['name']}.png"] + ([f"{entry['name']}.unused.png"] if entry.get("unused") else [])


def files(run: dict) -> list[str]:
    return [f for entry in run["blobs"] for f in item_files(run, entry)]


def blob_from_files(source: Path, entry: dict) -> blobs.Blob:
    size, pixels, colors = blobs.read_png(source / f"{entry['name']}.png")
    if size[0] % 8 or size[1] % 8:
        raise ValueError(f"{entry['name']}.png: {size[0]}x{size[1]} is not a multiple of 8 pixels")
    unused = []
    if entry.get("unused"):
        _, sheet, _ = blobs.read_png(source / f"{entry['name']}.unused.png")
        unused = blobs.unused_from_sheet(sheet, entry["unused"])
    flags0 = entry["flags"][0]
    palette = None
    if flags0 & 3:
        palette = blobs.encode_palette(colors, entry.get("highBits", []), 256 if flags0 & 1 else 16)
    return blobs.blob_from_image(*entry["flags"], palette, size[0] // 8, size[1] // 8, pixels, unused,
                                   entry.get("layout"))


def build(source: Path, name: str, settings: dict, entry: dict) -> list[tuple[str, bytes]]:
    return [(entry.get("symbol", f"g{entry['name']}"), blobs.build(blob_from_files(source, entry)))]


def manifest_labels(ver: str) -> dict[int, str]:
    """Address to symbol for the `label` rows of regions.<ver>.txt."""
    labels = {}
    for raw in (ROOT / f"regions.{ver}.txt").read_text().splitlines():
        parts = raw.split("#", 1)[0].split()
        if len(parts) == 3 and parts[0] == "label":
            labels[int(parts[1], 16)] = parts[2]
    return labels


# BgGraphicNNN numbers (1-based, after the battle backgrounds) at which a
# battle effect's frames start; each runs up to the next start.
EFFECT_STARTS = (8, 22, 58, 104, 156)


# Blobs without a palette draw with one that is already loaded. Their PNGs show
# the colors of the blob or label named here (recorded as `palette`). Whether
# each source is the palette the game actually uses is only established for
# the menu screen frame (see docs/memory-map/menu_screen.md).
PALETTE_SOURCES = {
    "PatronusCutscene": {f"PatronusCutscene{n:03d}": "PatronusCutscene001" for n in range(2, 7)},
    "CutsceneDrawingsStartup": {"CutsceneDrawingsStartup001": "g_MenuBg3Graphic",
                                "CutsceneDrawingsStartup013": "g_MenuBg3Graphic"},
    "HippogriffLanguageMinigameBgs": {"MenuScreenGraphic": "g_MenuBg3Graphic"},
}


def names(bank: str, labels: dict[int, str]):
    """Blob names by position. The first 28 blobs of BgGraphics are the 14
    floor and wall pairs of the battle background table, the next two its
    alternate pair, then come single graphics and five battle effects'
    frames. Elsewhere a blob that has a `label` row in the manifest at its
    address takes that symbol (its name is the symbol without the `g_`),
    the rest are numbered."""
    def name(i: int, addr: int) -> str:
        if addr in labels and labels[addr].startswith("g_"):
            return labels[addr][2:]
        if bank == "BgGraphics":
            if i < 28:
                return f"Battle{'Floor' if i % 2 == 0 else 'Wall'}{i // 2 + 1:02d}"
            if i < 30:
                return f"BattleAlt{'Floor' if i % 2 == 0 else 'Wall'}"
            n = i - 29
            starts = [e for e in EFFECT_STARTS if e <= n]
            if starts:
                return f"BattleEffectBg{len(starts)}Frame{n - starts[-1] + 1:02d}"
            return f"BgGraphic{n:03d}"
        return f"{bank}{i + 1:03d}"
    return name


def gray_palette(bpp8: bool):
    return [((i if bpp8 else (i % 16) * 17),) * 3 for i in range(256)]


def walk(rom: bytes, start: int, end: int):
    addr, found = start, []
    while addr < end:
        blob, next_addr, raw = blobs.parse(rom, addr)
        found.append((addr, blob, raw))
        addr = next_addr
    if addr != end:
        raise ValueError(f"walk ends at {addr:#010x}, not the row end {end:#010x}")
    return found


def write_blob(source, name, symbol, palette_from, colors, blob, raw):
    high = []
    if blob.palette is not None:
        colors, high = blobs.decode_palette(blob.palette)
    size = (blob.width * 8, blob.height * 8)
    transparent = blobs.transparent_indices(blob.bpp8)
    blobs.write_png(source / f"{name}.png", size, blobs.image_pixels(blob), colors, transparent)
    entry = {"name": name, "flags": [blob.flags0, blob.flags1]}
    if symbol:
        entry["symbol"] = symbol
    if palette_from:
        entry["palette"] = palette_from
    if high:
        entry["highBits"] = high
    unused = blob.tiles[blobs.used_tiles(blob):]
    if unused:
        entry["unused"] = len(unused)
        size, pixels = blobs.unused_sheet(unused)
        blobs.write_png(source / f"{name}.unused.png", size, pixels, colors, transparent)
    rebuilt = blobs.build(blob_from_files(source, entry))
    if rebuilt != raw:
        entry["layout"] = blobs.layout_of(blob)
        rebuilt = blobs.build(blob_from_files(source, entry))
    if rebuilt != raw:
        raise ValueError(f"{name}: rebuilding from the PNGs gives different bytes")
    return entry


def extract(rom: bytes, ver: str, start: int, end: int, name: str, source: Path) -> dict:
    found = walk(rom, start, end)
    labels = manifest_labels(ver)
    namer = names(name, labels)
    jobs = []
    by_name = {}
    for i, (addr, blob, raw) in enumerate(found):
        label = labels.get(addr, "")
        by_name[namer(i, addr)] = (addr, blob)
        if label.startswith("g_"):
            by_name[label] = (addr, blob)
    for i, (addr, blob, raw) in enumerate(found):
        blob_name = namer(i, addr)
        wanted = PALETTE_SOURCES.get(name, {}).get(blob_name)
        colors = gray_palette(blob.bpp8)
        if wanted:
            if wanted in by_name:
                palette = by_name[wanted][1].palette
            else:
                addr_of = {v: k for k, v in labels.items()}[wanted]
                palette = blobs.parse(rom, addr_of)[0].palette
            colors, _ = blobs.decode_palette(palette)
        symbol = labels[addr] if labels.get(addr, "").startswith("g_") else None
        jobs.append((source, blob_name, symbol, wanted, colors, blob, raw))
    with ProcessPoolExecutor() as pool:
        return {"blobs": list(pool.map(write_blob, *zip(*jobs)))}
