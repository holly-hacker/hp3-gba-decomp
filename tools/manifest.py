#!/usr/bin/env python3
"""Parse regions.<ver>.txt, the manifest of extracted byte ranges.

Directive rows (krawall-module, dialog-text, c-file, ...) name a source
under data/, src/ or 3rd_party/ and resolve to the assembly some tools/ script packs
or compiles into build/<ver>/; lib-object rows name a toolchain library
object instead.
"""
import sys

# (start, end, asmfile, name); start and end are None for a row without
# an address, and end alone after a `_` end followed by such a row.
Region = tuple[int | None, int | None, str, str]
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

# graphics rows claim one group of graphics, described in
# graphics/<feature>.yaml; tools/graphics/pack_graphics.py packs it to
# build/<ver>/graphics/<name>.s.
GRAPHICS_DIRECTIVE = "graphics"

# c-file, c-file-O1 and c-file-arm rows name a .c under src/, compiled to
# assembly by tools/c/compile_c.py (the `compile-c` recipe, which must run
# before `gen-link`) with the compiler the ROM was built with -- see
# docs/compiler.md.
#
# c-file-gcc3 and c-file-gcc3-arm rows name a .c under 3rd_party/,
# compiled the same way with the GCC 3.0.2 Krawall was built with, and
# asm-file-cpp rows a .S that compile_c.py preprocesses. These objects
# keep their sections apart: the row places one of them, .text unless the
# optional <section> says otherwise, at <start>, or at the RAM address
# <vma> when given (code or data that runs from RAM, stored at <start>).
GCC3_C_DIRECTIVES = {"c-file-gcc3", "c-file-gcc3-arm"}
ASM_CPP_DIRECTIVE = "asm-file-cpp"
SECTIONED_DIRECTIVES = GCC3_C_DIRECTIVES | {ASM_CPP_DIRECTIVE}
C_FILE_DIRECTIVES = {"c-file", "c-file-O1", "c-file-arm"} | SECTIONED_DIRECTIVES

# c-rodata rows place the .rodata of the c-file/c-file-O1 row named <name>
# at their own address, for a C object whose read-only data the ROM keeps
# apart from its code. The region is named <name> + RODATA_SUFFIX.
C_RODATA_DIRECTIVE = "c-rodata"
RODATA_SUFFIX = ".rodata"

# c-data rows do the same for the object's .data, its initialised
# non-const data, which the ROM stores apart from its .rodata (a
# non-const table of string pointers, whose strings stay in .rodata).
# The region is named <name> + DATA_SUFFIX.
C_DATA_DIRECTIVE = "c-data"
DATA_SUFFIX = ".data"

# Directive -> region-name suffix for the rows that place one section of
# a c-file/c-file-O1 row's object.
SPLIT_SECTION_DIRECTIVES = {C_RODATA_DIRECTIVE: RODATA_SUFFIX,
                            C_DATA_DIRECTIVE: DATA_SUFFIX}

# c-section rows place one more section of a c-file-gcc3, c-file-gcc3-arm
# or asm-file-cpp row's object, named <name>, at <start> (or <vma>, as
# above). The region is named <name> + <section>.
C_SECTION_DIRECTIVE = "c-section"

# asm-file rows name a committed .s under asm/ directly -- no packing or
# compiling step, the file is already the region's assembly.
ASM_FILE_DIRECTIVE = "asm-file"

# lib-object rows name a member of an archive agbcc installs (libgcc.a,
# libc.a); tools/gen_link.py extracts it and links it unchanged. The region
# is named after the member without its .o. An optional last field places
# the member's .bss at that RAM address.
LIB_OBJECT_DIRECTIVE = "lib-object"


# Rows that name a single address rather than a range.
LABEL_DIRECTIVES = {"label", "thumb-func", "arm-func"}

# A region row's <end> may be written as this, meaning the start of the
# next region row. A row whose <start> is this too has no address: it
# holds code or data the original ROM does not have, placed after the row
# above it, and only links without the manifest address checks.
NEXT_START = "_"


def address(field: str) -> int | None:
    """A row's <start> or resolved <end>; None for a row without one."""
    return None if field == NEXT_START else int(field, 16)


def region_range(path: str, lineno: int, start_s: str, end_s: str) -> tuple[int | None, int | None]:
    start, end = address(start_s), address(end_s)
    if start is None:
        return None, None
    if end is not None and end <= start:
        sys.exit(f"{path}:{lineno}: end must be after start")
    return start, end


def read_rows(path: str) -> list[tuple[int, list[str]]]:
    """Returns (lineno, fields) for every row, with comments stripped and
    each `_` end resolved to the next region row's start."""
    rows = []
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            parts = raw_line.split("#", 1)[0].split()
            if parts:
                rows.append((lineno, parts))
    pending = None
    for lineno, parts in rows:
        if parts[0] in LABEL_DIRECTIVES:
            continue
        if pending is not None:
            if len(parts) < 2:
                sys.exit(f"{path}:{lineno}: expected a start address")
            pending[2] = parts[1]
            pending = None
        if len(parts) >= 3 and parts[2] == NEXT_START and parts[1] != NEXT_START:
            pending = parts
            pending_lineno = lineno
    if pending is not None:
        sys.exit(f"{path}:{pending_lineno}: '{NEXT_START}' end with no following region row")
    return rows


def read_lib_objects(path: str) -> dict[str, tuple[str, str, int | None]]:
    """Returns region name -> (archive, member, bss address or None) for
    every lib-object row."""
    out = {}
    for _, parts in read_rows(path):
        if parts[0] == LIB_OBJECT_DIRECTIVE:
            bss = int(parts[5], 16) if len(parts) == 6 else None
            out[parts[4][:-len(".o")]] = (parts[3], parts[4], bss)
    return out


def read_placements(path: str) -> dict[str, tuple[str, str, int | None]]:
    """Returns region name -> (object name, section, RAM address or None)
    for every region that places one section of a sectioned object."""
    out = {}
    for _, parts in read_rows(path):
        if parts[0] in SECTIONED_DIRECTIVES:
            section = parts[5] if len(parts) > 5 else ".text"
            vma = int(parts[6], 16) if len(parts) > 6 else None
            out[parts[4]] = (parts[4], section, vma)
        elif parts[0] == C_SECTION_DIRECTIVE:
            vma = int(parts[5], 16) if len(parts) > 5 else None
            out[parts[3] + parts[4]] = (parts[3], parts[4], vma)
    return out


def parse_manifest(path: str, ver: str) -> tuple[list[Region], Labels]:
    """Returns (regions, labels): regions in manifest order, which is
    address order for the rows that have one."""
    regions: list[Region] = []
    labels: Labels = {}
    for lineno, parts in read_rows(path):
        if parts[0] in LABEL_DIRECTIVES:
            if len(parts) != 3:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <addr> <name>'")
            addr = int(parts[1], 16)
            labels[addr] = (parts[2], parts[0] == "thumb-func")
            continue
        if parts[0] in KRAWALL_DIRECTIVES:
            if len(parts) != 5:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
            _, start_s, end_s, _source, name = parts
            start, end = region_range(path, lineno, start_s, end_s)
            kind = KRAWALL_DIRECTIVES[parts[0]]
            asmfile = f"build/{ver}/audio/{kind}/{name}.s"
            regions.append((start, end, asmfile, name))
            continue
        if parts[0] in SECTIONED_DIRECTIVES:
            if len(parts) not in (5, 6, 7):
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name> [<section> [<vma>]]'")
            _, start_s, end_s, _source, name = parts[:5]
            start, end = region_range(path, lineno, start_s, end_s)
            regions.append((start, end, f"build/{ver}/c/{name}.s", name))
            continue
        if parts[0] == C_SECTION_DIRECTIVE:
            if len(parts) not in (5, 6):
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <name> <section> [<vma>]'")
            _, start_s, end_s, name, section = parts[:5]
            start, end = region_range(path, lineno, start_s, end_s)
            regions.append((start, end, f"build/{ver}/c/{name}.s", name + section))
            continue
        if parts[0] in C_FILE_DIRECTIVES:
            if len(parts) != 5:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <source> <name>'")
            _, start_s, end_s, _source, name = parts
            start, end = region_range(path, lineno, start_s, end_s)
            asmfile = f"build/{ver}/c/{name}.s"
            regions.append((start, end, asmfile, name))
            continue
        if parts[0] in SPLIT_SECTION_DIRECTIVES:
            if len(parts) != 4:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <name>'")
            _, start_s, end_s, name = parts
            start, end = region_range(path, lineno, start_s, end_s)
            asmfile = f"build/{ver}/c/{name}.s"
            regions.append((start, end, asmfile, name + SPLIT_SECTION_DIRECTIVES[parts[0]]))
            continue
        if parts[0] == GRAPHICS_DIRECTIVE:
            if len(parts) != 5:
                sys.exit(f"{path}:{lineno}: expected 'graphics <start> <end> <feature> <group>'")
            _, start_s, end_s, _feature, name = parts
            start, end = region_range(path, lineno, start_s, end_s)
            regions.append((start, end, f"build/{ver}/graphics/{name}.s", name))
            continue
        if parts[0] in DIALOG_TEXT_DIRECTIVES:
            expected_len = 5 if parts[0] == "dialog-text" else 4
            if len(parts) != expected_len:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end>"
                          f"{' <json>' if parts[0] == 'dialog-text' else ''} <name>'")
            start_s, end_s, name = parts[1], parts[2], parts[-1]
            start, end = region_range(path, lineno, start_s, end_s)
            asmfile = f"build/{ver}/text/{name}.s"
            regions.append((start, end, asmfile, name))
            continue
        if parts[0] == LIB_OBJECT_DIRECTIVE:
            if len(parts) not in (5, 6):
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <archive> <member> [<bss>]'")
            start, end = region_range(path, lineno, parts[1], parts[2])
            archive, member = parts[3], parts[4]
            if not member.endswith(".o"):
                sys.exit(f"{path}:{lineno}: library member must be a .o")
            regions.append((start, end, f"{archive}({member})", member[:-len(".o")]))
            continue
        if parts[0] == ASM_FILE_DIRECTIVE:
            if len(parts) != 5:
                sys.exit(f"{path}:{lineno}: expected '{parts[0]} <start> <end> <asm-file> <name>'")
            _, start_s, end_s, asmfile, name = parts
            start, end = region_range(path, lineno, start_s, end_s)
            regions.append((start, end, asmfile, name))
            continue
        sys.exit(f"{path}:{lineno}: unrecognized directive '{parts[0]}'")
    names = {r[3] for r in regions}
    placements = read_placements(path)
    for r in regions:
        if r[3] in placements:
            if placements[r[3]][0] not in names:
                sys.exit(f"{path}: c-section row {r[3]} has no object row")
        else:
            for directive, suffix in SPLIT_SECTION_DIRECTIVES.items():
                if r[3].endswith(suffix) and r[3][:-len(suffix)] not in names:
                    sys.exit(f"{path}: {directive} row {r[3][:-len(suffix)]} has no c-file row")
    prev = None
    for r in regions:
        if r[0] is None:
            continue
        if prev is not None and r[0] < (prev[0] if prev[1] is None else prev[1]):
            sys.exit(f"{path}: regions out of order or overlapping: {prev} and {r}")
        prev = r
    return regions, labels
