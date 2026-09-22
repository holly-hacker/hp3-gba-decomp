#!/usr/bin/env python3
"""Parse regions.<ver>.txt, the manifest of extracted byte ranges.

Directive rows (krawall-module, dialog-text, c-file, ...) name a source
under data/ or src/ and resolve to the assembly some tools/ script packs
or compiles into build/<ver>/.
"""
import sys

# (start, end, asmfile, name)
Region = tuple[int, int, str, str]
# address -> (name, is_thumb), for symbols inside not-yet-extracted
# (still-incbin) territory that extracted code needs to reference.
# is_thumb marks a Thumb code entry point so the assembler sets the
# symbol's low address bit (`thumb-func` rows). `arm-func` rows are a
# confirmed ARM entry point; plain `label` rows are data, or an address
# whose code/data status or instruction mode hasn't been confirmed.
# Neither `arm-func` nor `label` sets the bit.
Labels = dict[int, tuple[str, bool]]


# krawall-module/krawall-samples rows name their JSON/directory source
# (data/audio/...) in column 3, not a directly includable file -- the
# actual assembly gets packed to this fixed build/ path by pack_krawall.py
# (see the `pack-krawall` recipe, which must run before `gen-link`).
KRAWALL_DIRECTIVES = {"krawall-module": "modules", "krawall-samples": "samples"}

# dialog-text/dialog-text-table rows: same idea, but pack_text.py names
# its build/<ver>/text/*.s output after the row's own <name> field
# directly (no modules/samples-style subdirectory split needed, since
# language files and the one pointer table all have distinct names).
DIALOG_TEXT_DIRECTIVES = {"dialog-text", "dialog-text-table"}

# battle-script-table rows: same idea as krawall-module, but packed from
# data/battle_scripts/scripts.json by pack_battle_scripts.py -- see
# docs/formats/battle_scripts.md.
BATTLE_SCRIPT_TABLE_DIRECTIVE = "battle-script-table"

# item-icon-data rows: same shape as krawall-samples (a directory of
# per-name files, not one JSON), packed by pack_item_icons.py from
# data/images/items/<Name>.palette.bin/.tiles.bin/.frames.bin -- see
# docs/formats/graphics.md's "Item icons" section.
ITEM_ICON_DATA_DIRECTIVE = "item-icon-data"

# c-file rows name a .c under src/, compiled to assembly by
# tools/c/compile_c.py (the `compile-c` recipe, which must run before
# `gen-link`) with the compiler the ROM was built with -- see
# docs/compiler.md.
C_FILE_DIRECTIVE = "c-file"

# asm-file rows name a committed .s under asm/ directly -- no packing or
# compiling step, the file is already the region's assembly.
ASM_FILE_DIRECTIVE = "asm-file"


def parse_manifest(path: str, ver: str) -> tuple[list[Region], Labels]:
    """Returns (regions, labels): regions sorted and non-overlapping."""
    regions: list[Region] = []
    labels: Labels = {}
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            if parts[0] in ("label", "thumb-func", "arm-func"):
                if len(parts) != 3:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <addr> <name>'")
                addr = int(parts[1], 16)
                labels[addr] = (parts[2], parts[0] == "thumb-func")
                continue
            if parts[0] in KRAWALL_DIRECTIVES:
                if len(parts) != 5:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
                _, start_s, end_s, _source, name = parts
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                kind = KRAWALL_DIRECTIVES[parts[0]]
                asmfile = f"build/{ver}/audio/{kind}/{name}.s"
                regions.append((start, end, asmfile, name))
                continue
            if parts[0] == BATTLE_SCRIPT_TABLE_DIRECTIVE:
                if len(parts) != 5:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
                _, start_s, end_s, _source, name = parts
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                asmfile = f"build/{ver}/battle_scripts/{name}.s"
                regions.append((start, end, asmfile, name))
                continue
            if parts[0] == C_FILE_DIRECTIVE:
                if len(parts) != 5:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
                _, start_s, end_s, _source, name = parts
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                asmfile = f"build/{ver}/c/{name}.s"
                regions.append((start, end, asmfile, name))
                continue
            if parts[0] == ITEM_ICON_DATA_DIRECTIVE:
                if len(parts) != 5:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
                _, start_s, end_s, _source, name = parts
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                asmfile = f"build/{ver}/items/{name}.s"
                regions.append((start, end, asmfile, name))
                continue
            if parts[0] in DIALOG_TEXT_DIRECTIVES:
                expected_len = 5 if parts[0] == "dialog-text" else 4
                if len(parts) != expected_len:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end>"
                              f"{' <json>' if parts[0] == 'dialog-text' else ''} <name>'")
                start_s, end_s, name = parts[1], parts[2], parts[-1]
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                asmfile = f"build/{ver}/text/{name}.s"
                regions.append((start, end, asmfile, name))
                continue
            if parts[0] == ASM_FILE_DIRECTIVE:
                if len(parts) != 5:
                    sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <asm-file> <name>'")
                _, start_s, end_s, asmfile, name = parts
                start, end = int(start_s, 16), int(end_s, 16)
                if end <= start:
                    sys.exit(f"{path}:{lineno}: end must be after start")
                regions.append((start, end, asmfile, name))
                continue
            sys.exit(f"{path}:{lineno}: unrecognized directive '{parts[0]}'")
    regions.sort(key=lambda r: r[0])
    for i in range(1, len(regions)):
        if regions[i][0] < regions[i - 1][1]:
            sys.exit(f"overlapping regions: {regions[i-1]} and {regions[i]}")
    return regions, labels
