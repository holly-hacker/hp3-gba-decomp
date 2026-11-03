#!/usr/bin/env python3
"""Parse regions.<ver>.txt, the manifest of the ROM's regions in link order.

Directive rows (krawall-module, dialog-text, c-file, ...) name a source
under data/, src/ or 3rd_party/ and resolve to the assembly some tools/ script packs
or compiles into build/<ver>/; lib-object rows name a toolchain library
object instead.
"""
import os
import re
import sys

# (asmfile, name)
Region = tuple[str, str]
# region name -> label name, from `label <region> <name>` rows: a symbol
# for where that region is stored, which no source defines.
Labels = dict[str, str]


# krawall-module/krawall-samples rows name their JSON/directory source
# (data/audio/...), not a directly includable file -- the
# actual assembly gets packed to this fixed build/ path by pack_krawall.py.
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
# assembly by tools/c/compile_c.py with the compiler the ROM was built
# with -- see docs/compiler.md.
#
# c-file-gcc3 and c-file-gcc3-arm rows name a .c under 3rd_party/,
# compiled the same way with the GCC 3.0.2 Krawall was built with, and
# asm-file-cpp rows a .S that compile_c.py preprocesses. These objects
# keep their sections apart: the row places .text, and c-rodata, c-iwram
# and c-ewram rows place the others.
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

# `c-iwram <name> [<address>]` and `c-ewram <name> [<address>]` rows place
# the .iwram or .ewram section of the object <name>: code or data stored in
# ROM that Krawall copies to RAM and runs there. The first row of each
# gives the RAM address the section starts at; the rows after it follow
# on. The region is named <name> + the section.
RAM_SECTION_DIRECTIVES = {"c-iwram": ".iwram", "c-ewram": ".ewram"}

# Directive -> region-name suffix, which is also the section placed, for
# the rows that place one section of an object another row names.
SPLIT_SECTION_DIRECTIVES = {C_RODATA_DIRECTIVE: RODATA_SUFFIX,
                            C_DATA_DIRECTIVE: DATA_SUFFIX,
                            **RAM_SECTION_DIRECTIVES}

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


def read_ram_addresses(path: str) -> dict[str, int | None]:
    """Returns region name -> RAM address for every c-iwram and c-ewram row:
    the address its section starts at, or None if it follows the row
    above."""
    out = {}
    for _, parts in read_rows(path):
        if parts[0] in RAM_SECTION_DIRECTIVES:
            address = int(parts[2], 16) if len(parts) > 2 else None
            out[parts[1] + RAM_SECTION_DIRECTIVES[parts[0]]] = address
    return out


def parse_manifest(path: str, ver: str) -> tuple[list[Region], Labels]:
    """Returns (regions, labels), regions in manifest order."""
    regions: list[Region] = []
    labels: Labels = {}
    ram_started: set[str] = set()
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
        elif directive in C_FILE_DIRECTIVES:
            expect(2, 2, "<source> <name>")
            regions.append((f"build/{ver}/c/{args[1]}.s", args[1]))
        elif directive in RAM_SECTION_DIRECTIVES:
            expect(1, 2, "<name> [<address>]")
            if len(args) == 1 and directive not in ram_started:
                sys.exit(f"{path}:{lineno}: the first {directive} row needs an address")
            ram_started.add(directive)
            suffix = RAM_SECTION_DIRECTIVES[directive]
            regions.append((f"build/{ver}/c/{args[0]}.s", args[0] + suffix))
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
    for _, name in regions:
        for directive, suffix in SPLIT_SECTION_DIRECTIVES.items():
            if name.endswith(suffix) and name[:-len(suffix)] not in names:
                sys.exit(f"{path}: {directive} row {name[:-len(suffix)]} has no object row")
    return regions, labels


def ram_symbols_source(ver: str) -> str:
    """The assembly tools/gen_link.py writes to define the RAM variables."""
    return f"build/{ver}/ram_symbols.s"


def object_path(ver: str, source: str) -> str:
    """The object a region's source assembles to: under build/<ver>/obj/ at
    the source's own path, so every region placing a section of one source
    shares its object. A lib-object row's archive(member) goes to
    <archive>/<member>."""
    lib = re.fullmatch(r"(\w+)\.a\((.+)\)", source)
    rel = f"{lib[1]}/{lib[2]}" if lib else source.removeprefix(f"build/{ver}/")
    return f"build/{ver}/obj/{os.path.splitext(rel)[0]}.o"
