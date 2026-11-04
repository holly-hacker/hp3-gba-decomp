"""The linker script for regions.<ver>.txt, which tools/configure.py writes
to build/<ver>/link.ld.

It places every region's section one after another, in manifest order,
each at its own alignment, and brackets each in __rgn_<name>_beg/_end
markers. It names every object it links, so an object of a region that no
longer exists is left out. A region that assembles to a different size
moves everything after it; tools/compare.py names the region where the
build first differs.

Usage: link_script.py <map>   (lists the unplaced sections of a failed link)
"""
import io
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import (  # noqa: E402
    SPLIT_SECTION_DIRECTIVES,
    object_path,
    parse_manifest,
    ram_symbols_object,
    read_lib_objects,
    read_ram_addresses,
)
from rom_elf import ROM_BASE  # noqa: E402


def link_script(ver: str) -> str:
    regions, labels = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    ram_addresses = read_ram_addresses(f"regions.{ver}.txt")
    names = {name for _, name in regions}
    objects = {name: object_path(ver, source) for source, name in regions}

    # placements, in link order: (output section, object, input section,
    # region name). A row that places one section of an object another row
    # names takes that section, and a C object's own row its .text. Any
    # other row takes its object's .text and .rodata: an asset's data is
    # all .rodata.
    placements = []
    for i, (source, name) in enumerate(regions):
        section = next((s for s in SPLIT_SECTION_DIRECTIVES.values()
                        if name.endswith(s) and name[:-len(s)] in names), None)
        if section is None:
            c_object = os.path.dirname(source) == f"build/{ver}/c"
            section = ".text" if c_object else ".text .rodata"
        placements.append((f".rgn{i:03d}", objects[name], section, name))

    with io.StringIO() as f:
        f.write(f"INPUT({ram_symbols_object(ver)})\n")
        f.write("SECTIONS\n{\n")
        # The game's own RAM variables are fixed addresses
        # (ram_symbols.<ver>.inc); a library object's .bss is placed where
        # the ROM's references to it point. These come first, so the
        # location counter only ever moves forward.
        for i, (name, (_, _, bss)) in enumerate(sorted(lib_objects.items())):
            if bss is not None:
                f.write(f"    .libbss{i:03d} {hex(bss)} (NOLOAD) : "
                        f"{{ {objects[name]}(.bss) }}\n")
        f.write(f"    . = {hex(ROM_BASE)};\n")
        prev, prev_runs_from_ram = None, False
        for section, obj, input_section, region_name in placements:
            runs_from_ram = region_name in ram_addresses
            # The markers bracket the region's content in the linked ELF.
            contents = (f'"__rgn_{region_name}_beg" = .; '
                        f'{obj}({input_section}) '
                        f'"__rgn_{region_name}_end" = .;')
            # Each section is stored right after the previous one, at its
            # own alignment. A section that runs from RAM is linked at its
            # RAM address (the row's, or right after the previous RAM
            # section), which leaves the location counter there, so the
            # next ROM section restarts it from where that one is stored and
            # states that it is stored where it runs: ld would otherwise
            # keep the RAM section's offset between the two.
            if not runs_from_ram and prev_runs_from_ram:
                f.write(f"    . = LOADADDR({prev}) + SIZEOF({prev});\n")
                f.write(f"    {section} : AT(ADDR({section})) {{ {contents} }}\n")
            elif not runs_from_ram:
                f.write(f"    {section} : {{ {contents} }}\n")
            else:
                address = ram_addresses[region_name]
                at = f" {hex(address)}" if address is not None else ""
                stored = f"ALIGN(LOADADDR({prev}) + SIZEOF({prev}), ALIGNOF({section}))"
                f.write(f"    {section}{at} : AT({stored}) {{ {contents} }}\n")
            prev, prev_runs_from_ram = section, runs_from_ram
        # A label row names a symbol the original link supplied and no
        # source defines, such as where a RAM image is stored or an empty
        # table that shares the next object's address: where its region
        # is stored.
        for i, (_, name) in enumerate(regions):
            if name in labels:
                f.write(f"    {labels[name]} = LOADADDR(.rgn{i:03d});\n")
        f.write("    /DISCARD/ : { *(.comment) *(.ARM.attributes) *(.note*) }\n")
        # Anything still unplaced is a section of an object that no
        # manifest row places; ld would otherwise put it where it likes.
        f.write("    .unplaced : { *(*) }\n")
        f.write(f'    ASSERT(SIZEOF(.unplaced) == 0, "an object has a section '
                f'that no regions.{ver}.txt row places")\n')
        f.write("}\n")
        return f.getvalue()


def unplaced(map_path: str) -> list[str]:
    """The non-empty input sections a link map shows in .unplaced, as
    "<object>: <section> (<size> bytes)"."""
    with open(map_path) as f:
        lines = f.read().splitlines()
    start = next(i for i, line in enumerate(lines) if line.startswith(".unplaced"))
    out, name = [], None
    for line in lines[start + 1:]:
        if line and not line[0].isspace():
            break
        fields = line.split()
        # A long section name gets a line of its own.
        if len(fields) == 1:
            name = fields[0]
            continue
        if len(fields) == 4:
            name, fields = fields[0], fields[1:]
        if len(fields) == 3 and fields[2].endswith(".o") and int(fields[1], 16):
            out.append(f"{fields[2]}: {name} ({int(fields[1], 16)} bytes)")
    return out


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <map>")
    for entry in unplaced(sys.argv[1]):
        print(f"unplaced: {entry}", file=sys.stderr)
