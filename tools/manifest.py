#!/usr/bin/env python3
"""Parse regions.<ver>.txt, the manifest of the ROM's regions in link order.

Directive rows (krawall-module, dialog-text, c-file, ...) name a source
under data/, src/ or 3rd_party/ and resolve to the assembly some tools/ script packs
or compiles into build/<ver>/; lib-object rows name a toolchain library
object instead.
"""
import sys

# (asmfile, name)
Region = tuple[str, str]
# region name -> label name, from `label <region> <name>` rows: a symbol
# for where that region is stored, which no source defines.
Labels = dict[str, str]


# krawall-module/krawall-samples rows name their JSON/directory source
# (data/audio/...), not a directly includable file -- the
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
# optional <section> says otherwise, linked at the RAM address <vma> when
# given (code or data that runs from RAM, stored in ROM).
GCC3_C_DIRECTIVES = {"c-file-gcc3", "c-file-gcc3-arm"}
ASM_CPP_DIRECTIVE = "asm-file-cpp"
SECTIONED_DIRECTIVES = GCC3_C_DIRECTIVES | {ASM_CPP_DIRECTIVE}
C_FILE_DIRECTIVES = {"c-file", "c-file-O1", "c-file-arm"} | SECTIONED_DIRECTIVES

# c-rodata rows place the .rodata of the c-file/c-file-O1 row named <name>
# as a region of its own, for a C object whose read-only data the ROM keeps
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
# or asm-file-cpp row's object, named <name> (at <vma>, as above, when
# given). The region is named <name> + <section>.
C_SECTION_DIRECTIVE = "c-section"

# asm-file rows name a committed .s under asm/ directly -- no packing or
# compiling step, the file is already the region's assembly.
ASM_FILE_DIRECTIVE = "asm-file"

# lib-object rows name a member of an archive agbcc installs (libgcc.a,
# libc.a); tools/gen_link.py extracts it and links it unchanged. The region
# is named after the member without its .o. An optional last field places
# the member's .bss at that RAM address.
LIB_OBJECT_DIRECTIVE = "lib-object"


# `label <region> <name>` rows.
LABEL_DIRECTIVE = "label"


def read_rows(path: str) -> list[tuple[int, list[str]]]:
    """Returns (lineno, fields) for every row, with comments stripped."""
    rows = []
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            parts = raw_line.split("#", 1)[0].split()
            if parts:
                rows.append((lineno, parts))
    return rows


def read_lib_objects(path: str) -> dict[str, tuple[str, str, int | None]]:
    """Returns region name -> (archive, member, bss address or None) for
    every lib-object row."""
    out = {}
    for _, parts in read_rows(path):
        if parts[0] == LIB_OBJECT_DIRECTIVE:
            bss = int(parts[3], 16) if len(parts) == 4 else None
            out[parts[2][:-len(".o")]] = (parts[1], parts[2], bss)
    return out


def read_placements(path: str) -> dict[str, tuple[str, str, int | None]]:
    """Returns region name -> (object name, section, RAM address or None)
    for every region that places one section of a sectioned object."""
    out = {}
    for _, parts in read_rows(path):
        if parts[0] in SECTIONED_DIRECTIVES:
            section = parts[3] if len(parts) > 3 else ".text"
            vma = int(parts[4], 16) if len(parts) > 4 else None
            out[parts[2]] = (parts[2], section, vma)
        elif parts[0] == C_SECTION_DIRECTIVE:
            vma = int(parts[3], 16) if len(parts) > 3 else None
            out[parts[1] + parts[2]] = (parts[1], parts[2], vma)
    return out


def parse_manifest(path: str, ver: str) -> tuple[list[Region], Labels]:
    """Returns (regions, labels), regions in manifest order."""
    regions: list[Region] = []
    labels: Labels = {}
    for lineno, parts in read_rows(path):
        directive, args = parts[0], parts[1:]

        def expect(fewest: int, most: int, usage: str) -> None:
            if not fewest <= len(args) <= most:
                sys.exit(f"{path}:{lineno}: expected '{directive} {usage}'")

        if directive == LABEL_DIRECTIVE:
            expect(2, 2, "<region> <name>")
            labels[args[0]] = args[1]
        elif directive in KRAWALL_DIRECTIVES:
            expect(2, 2, "<source> <name>")
            kind = KRAWALL_DIRECTIVES[directive]
            regions.append((f"build/{ver}/audio/{kind}/{args[1]}.s", args[1]))
        elif directive in SECTIONED_DIRECTIVES:
            expect(2, 4, "<source> <name> [<section> [<vma>]]")
            regions.append((f"build/{ver}/c/{args[1]}.s", args[1]))
        elif directive == C_SECTION_DIRECTIVE:
            expect(2, 3, "<name> <section> [<vma>]")
            regions.append((f"build/{ver}/c/{args[0]}.s", args[0] + args[1]))
        elif directive in C_FILE_DIRECTIVES:
            expect(2, 2, "<source> <name>")
            regions.append((f"build/{ver}/c/{args[1]}.s", args[1]))
        elif directive in SPLIT_SECTION_DIRECTIVES:
            expect(1, 1, "<name>")
            suffix = SPLIT_SECTION_DIRECTIVES[directive]
            regions.append((f"build/{ver}/c/{args[0]}.s", args[0] + suffix))
        elif directive == GRAPHICS_DIRECTIVE:
            expect(2, 2, "<feature> <group>")
            regions.append((f"build/{ver}/graphics/{args[1]}.s", args[1]))
        elif directive in DIALOG_TEXT_DIRECTIVES:
            if directive == "dialog-text":
                expect(2, 2, "<json> <name>")
            else:
                expect(1, 1, "<name>")
            regions.append((f"build/{ver}/text/{args[-1]}.s", args[-1]))
        elif directive == LIB_OBJECT_DIRECTIVE:
            expect(2, 3, "<archive> <member> [<bss>]")
            if not args[1].endswith(".o"):
                sys.exit(f"{path}:{lineno}: library member must be a .o")
            regions.append((f"{args[0]}({args[1]})", args[1][:-len(".o")]))
        elif directive == ASM_FILE_DIRECTIVE:
            expect(2, 2, "<asm-file> <name>")
            regions.append((args[0], args[1]))
        else:
            sys.exit(f"{path}:{lineno}: unrecognized directive '{directive}'")
    names = {name for _, name in regions}
    if len(names) != len(regions):
        sys.exit(f"{path}: region names must be unique")
    for region, label in labels.items():
        if region not in names:
            sys.exit(f"{path}: label {label} names no region {region}")
    placements = read_placements(path)
    for _, name in regions:
        if name in placements:
            if placements[name][0] not in names:
                sys.exit(f"{path}: c-section row {name} has no object row")
        else:
            for directive, suffix in SPLIT_SECTION_DIRECTIVES.items():
                if name.endswith(suffix) and name[:-len(suffix)] not in names:
                    sys.exit(f"{path}: {directive} row {name[:-len(suffix)]} has no c-file row")
    return regions, labels
