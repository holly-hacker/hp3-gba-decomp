"""image-bank runs: indexed PNG sprites and palettes (see tools/images/sprite.py).

Settings: `bpp` (4 or 8), `componentOrder` (the ROM order of each image's
palette/tiles/frames components), optional `paletteHeader`/`paletteTrailer`
bytes around every palette, and the ordered `images` list. Each component
is labeled g<Image><Component>. See docs/formats/graphics.md ("Sprite
images").
"""
import re
import struct
from pathlib import Path

from sprite import (COMPONENT_KINDS, COMPRESSION_TYPES, OAM_SHAPES, build as build_image, component_length,
                    extract_images, image_files, tile_stream_length)

ROM_BASE = 0x08000000
ITEMS = "images"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
RUN_KEYS = {"bpp", "componentOrder", "images"}
OPTIONAL_RUN_KEYS = {"paletteHeader", "paletteTrailer"}
ENTRY_KEYS = [
    {"name", "offset", "compression"},
    {"name", "palette", "header", "frames"},
    {"name", "palette", "header", "frames", "bpp"},
    {"name", "paletteOnly"},
    {"name", "paletteOnly", "highBits"},
]
FRAME_KEYS = {"offset", "compression", "cells", "parts", "extra"}
OPTIONAL_FRAME_KEYS = {"padding"}


def _ints(value, count: int, what: str) -> None:
    if (not isinstance(value, list) or len(value) != count
            or not all(isinstance(v, int) and not isinstance(v, bool) for v in value)):
        raise ValueError(f"{what} must be a list of {count} integers")


def check_compression(value) -> None:
    if value not in COMPRESSION_TYPES:
        raise ValueError(f"compression must be one of {', '.join(COMPRESSION_TYPES)}")


def check_entry(image: dict) -> None:
    if image.get("paletteOnly") is not None:
        if image["paletteOnly"] is not True:
            raise ValueError("paletteOnly must be true")
        _ints(image.get("highBits", []), len(image.get("highBits", [])), "highBits")
        if not all(0 <= i < 1 << 8 for i in image.get("highBits", [])):
            raise ValueError("highBits must be palette indices")
        return
    if "offset" in image:
        check_compression(image["compression"])
        _ints(image["offset"], 2, "offset")
        return
    if not isinstance(image["palette"], bool):
        raise ValueError("palette must be true or false")
    if image.get("bpp", 4) not in (4, 8) or ("bpp" in image and image["palette"]):
        raise ValueError("bpp must be 4 or 8, on a sprite without its own palette")
    _ints(image["header"], 4, "header")
    frames = image["frames"]
    if not isinstance(frames, list) or not frames:
        raise ValueError("frames must be a nonempty list")
    for frame in frames:
        if not isinstance(frame, dict) or not FRAME_KEYS <= set(frame) <= FRAME_KEYS | OPTIONAL_FRAME_KEYS:
            raise ValueError(f"each frame needs {', '.join(sorted(FRAME_KEYS))} "
                             f"(optionally {', '.join(sorted(OPTIONAL_FRAME_KEYS))})")
        check_compression(frame["compression"])
        if "padding" in frame:
            _ints(frame["padding"], len(frame["padding"]), "padding")
            if not all(0 <= b <= 0xFF for b in frame["padding"]):
                raise ValueError("padding must be a list of bytes")
        _ints(frame["offset"], 2, "frame offset")
        for cell in frame["cells"]:
            _ints(cell, 4, "cell")
            if tuple(cell[2:]) not in OAM_SHAPES:
                raise ValueError(f"cell size {cell[2]}x{cell[3]} is not an OAM shape")
        for part in frame["parts"]:
            _ints(part, 6, "part")
        _ints(frame["extra"], len(frame["extra"]), "extra")


def check(run: dict) -> None:
    if not RUN_KEYS <= set(run) <= RUN_KEYS | OPTIONAL_RUN_KEYS:
        raise ValueError(f"expected {', '.join(sorted(RUN_KEYS))} "
                         f"(optionally {', '.join(sorted(OPTIONAL_RUN_KEYS))})")
    for key in OPTIONAL_RUN_KEYS & set(run):
        _ints(run[key], len(run[key]), key)
        if not all(0 <= b <= 0xFF for b in run[key]):
            raise ValueError(f"{key} must be a list of bytes")
    if run["bpp"] not in (4, 8):
        raise ValueError("bpp must be 4 or 8")
    order = run["componentOrder"]
    if not order or len(set(order)) != len(order) or not set(order) <= set(COMPONENT_KINDS):
        raise ValueError(f"componentOrder must list distinct kinds from {', '.join(COMPONENT_KINDS)}")
    images = run["images"]
    if not isinstance(images, list) or not images:
        raise ValueError("images must be a nonempty list")
    names = set()
    for i, image in enumerate(images):
        if not isinstance(image, dict) or set(image) not in ENTRY_KEYS:
            raise ValueError(f"image {i} has an unrecognized set of keys")
        name = image["name"]
        if not isinstance(name, str) or not SYMBOL.fullmatch(name) or name in names:
            raise ValueError(f"invalid or duplicate image name {name!r}")
        names.add(name)
        try:
            check_entry(image)
        except (ValueError, TypeError) as exc:
            raise ValueError(f"{name}: {exc}") from None


def files(run: dict) -> list[str]:
    return [f for image in run["images"] for f in image_files(image)]


def item_files(run: dict, image: dict) -> list[str]:
    return image_files(image)


def build(source: Path, name: str, settings: dict, image: dict) -> list[tuple[str, bytes]]:
    try:
        components = build_image(source, image, settings["bpp"])
    except (OSError, ValueError) as exc:
        raise ValueError(f"{source / image['name']}: {exc}") from None
    missing = set(components) - set(settings["componentOrder"])
    if missing:
        raise ValueError(f"{name}: {image['name']} has {', '.join(sorted(missing))} outside componentOrder")
    pieces = []
    for kind in settings["componentOrder"]:
        if kind in components:
            data = components[kind]
            if kind == "palette":
                data = bytes(settings.get("paletteHeader", [])) + data + bytes(settings.get("paletteTrailer", []))
            pieces.append((f"g{image['name']}{kind.capitalize()}", data))
    return pieces


# Extraction settings of each run; ROM ranges live in the manifests.
# storedCells banks keep each frame's OAM cells in their settings; their palette
# is optional per sprite, and a palette not followed by tiles is its own entry.
# noPalette lists sprites whose following palette belongs to other records
# (so it becomes the next, palette-only entry). names replaces the default
# positional name of entries whose labels C code uses. paletteHeader and
# paletteTrailer are bytes that surround every palette in the bank; they
# must be identical across the bank and are kept in the run's settings.
BANKS = {
    "ItemIcons": {"prefix": "Item", "bpp": 4, "componentOrder": ("palette", "tiles", "frames")},
    "HelpSprites": {"prefix": "Help", "bpp": 4, "componentOrder": ("tiles", "frames", "palette")},
    "Portraits": {"prefix": "Portrait", "bpp": 8, "componentOrder": ("tiles", "frames", "palette")},
    "MonsterOverworldSprites": {"prefix": "MonsterOverworld", "bpp": 4,
                                "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "UnnamedSprites": {"prefix": "Unnamed", "bpp": 4,
                       "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "BattleHudItems": {"prefix": "BattleHudItem", "bpp": 4,
                        "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "MonsterPalettes": {"prefix": "MonsterPalette", "bpp": 4, "componentOrder": ("palette",)},
    "RoomAltPalettes": {"prefix": "RoomAltPalette", "bpp": 8, "componentOrder": ("palette",),
                        "paletteHeader": [0xA1, 0x00], "paletteTrailer": [0x00, 0x00]},
    "AllyHeads": {"prefix": "AllyHead", "bpp": 4,
                  "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "MonsterBattleSprites": {"prefix": "MonsterBattle", "bpp": 4,
                             "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                             "noPalette": ("MonsterBattle025",)},
    "BattleIcons": {"prefix": "BattleIcon", "bpp": 4,
                    "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                    "noPalette": ("BattleIcon036",)},
    "BattleEffects": {"prefix": "BattleEffect", "bpp": 4,
                      "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                      "noPalette": ("BattleEffect020",)},
    "StatusCharacters": {"prefix": "StatusCharacter", "bpp": 8,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "BattleEffects2": {"prefix": "BattleEffect2_", "bpp": 4,
                       "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "MenuSprites": {"prefix": "MenuSprite", "bpp": 4,
                    "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                    "names": {"MenuSprite001": "MainMenu", "MenuSprite002": "DebugMenuCursor"}},
    "ObjectSprites": {"prefix": "ObjectSprite", "bpp": 4,
                      "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                      "names": {"ObjectSprite001": "HarryVsDementorsObject18",
                                "ObjectSprite002": "HarryVsDementorsObject1C",
                                "ObjectSprite095": "StatusEquipSlotCursor",
                                "ObjectSprite102": "ClockSkipObject1",
                                "ObjectSprite103": "ClockSkipObject2"}},
    "OptionIconUs": {"prefix": "OptionIconUs", "bpp": 4,
                     "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "ObjectSprites2": {"prefix": "ObjectSprite2_", "bpp": 4,
                       "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "ObjectPalettes": {"prefix": "ObjectPalette", "bpp": 4, "componentOrder": ("palette",)},
    "OverworldSpellEffects": {"prefix": "OverworldSpellEffect", "bpp": 4,
                        "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "OverworldPlayerSprites": {"prefix": "OverworldPlayer", "bpp": 4,
                        "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "LumosParticles": {"prefix": "LumosParticle", "bpp": 4,
                        "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "OwlCareSprites": {"prefix": "OwlCare", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "WizardCrackerSprites": {"prefix": "WizardCracker", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "PumpkinSprites": {"prefix": "Pumpkin", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "DivinationTeaSprites": {"prefix": "DivinationTea", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "HippogriffGlideSprites": {"prefix": "HippogriffGlide", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "HippogriffRiddikulusSprites": {"prefix": "HippogriffRiddikulus", "bpp": 4,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True,
                         "names": {"HippogriffRiddikulus001": "HippogriffFliesIntoAir", "HippogriffRiddikulus002": "HippogriffFliesIntoAir2"}},
    "Chatheads": {"prefix": "Chathead", "bpp": 8,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "FamousWizardCards": {"prefix": "FamousWizardCard", "bpp": 8,
                         "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "FighterSprites": {"prefix": "Fighter", "bpp": 4,
                       "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "BattleFaces": {"prefix": "BattleFace", "bpp": 8,
                    "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
    "ActionIcons": {"prefix": "ActionIcon", "bpp": 4,
                    "componentOrder": ("tiles", "frames", "palette"), "storedCells": True},
}


def split_bank(rom: bytes, start: int, end: int, name: str) -> list[tuple[str, dict[str, bytes]]]:
    settings = BANKS[name]
    bpp, stored = settings["bpp"], settings.get("storedCells", False)
    entries = []
    cursor, limit = start - ROM_BASE, end - ROM_BASE
    while cursor < limit:
        entry_name = f"{settings['prefix']}{len(entries) + 1:03d}"
        entry_name = settings.get("names", {}).get(entry_name, entry_name)
        components = {}
        if stored and tile_stream_length(rom[cursor:limit]) is None:
            components["palette"] = rom[cursor:cursor + (2 << bpp)]
            cursor += 2 << bpp
            entries.append((entry_name, components))
            continue
        for kind in settings["componentOrder"]:
            start_at = cursor
            try:
                if kind == "tiles":
                    # One stream per frame, back to back.
                    while cursor < limit and (length := tile_stream_length(rom[cursor:limit])):
                        cursor += length
                    if cursor == start_at:
                        raise ValueError("no tile stream starts here")
                elif kind == "palette" and stored and (
                        cursor >= limit or entry_name in settings.get("noPalette", ())
                        or tile_stream_length(rom[cursor:limit]) is not None):
                    continue
                elif kind == "palette":
                    header, trailer = settings.get("paletteHeader", []), settings.get("paletteTrailer", [])
                    if list(rom[cursor:cursor + len(header)]) != header:
                        raise ValueError(f"palette header is not {bytes(header).hex()}")
                    cursor += len(header)
                    palette_at = cursor
                    cursor += component_length(kind, rom[cursor:limit], bpp)
                    if list(rom[cursor:cursor + len(trailer)]) != trailer:
                        raise ValueError(f"palette trailer is not {bytes(trailer).hex()}")
                    components[kind] = rom[palette_at:cursor]
                    cursor += len(trailer)
                    continue
                else:
                    cursor += component_length(kind, rom[cursor:limit], bpp)
            except (ValueError, IndexError, struct.error) as exc:
                raise ValueError(f"{name}: {entry_name} {kind} at {start_at + ROM_BASE:#010x}: {exc}") from None
            components[kind] = rom[start_at:cursor]
        entries.append((entry_name, components))
    if cursor != limit:
        raise ValueError(f"{name}: walk ends at {cursor + ROM_BASE:#010x}, past the bank end {end:#010x}")
    return entries


def extract(rom: bytes, ver: str, start: int, end: int, name: str, source: Path) -> dict:
    if name not in BANKS:
        raise ValueError(f"no extraction settings for image bank {name}")
    settings = BANKS[name]
    images = extract_images(source, settings["bpp"], split_bank(rom, start, end, name),
                            settings.get("storedCells", False))
    run = {"bpp": settings["bpp"], "componentOrder": list(settings["componentOrder"])}
    for key in OPTIONAL_RUN_KEYS & set(settings):
        run[key] = settings[key]
    run["images"] = images
    return run
