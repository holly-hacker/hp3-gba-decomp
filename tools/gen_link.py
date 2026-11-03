#!/usr/bin/env python3
"""Write the linker script for regions.<ver>.txt.

Writes, all under build/<ver>/ and none of it committed:

  link.ld             places every region's section one after another, in
                      manifest order, each at its own alignment
  ram_symbols.s       the RAM variables of ram_symbols.<ver>.inc as global
                      symbols
  obj/<archive>/<member>.o
                      a lib-object row's member, extracted unchanged from
                      agbcc's installed archive

link.ld names every object it links, so an object of a region that no
longer exists is left out. tools/assemble.py assembles every other object.
A region that assembles to a different size moves everything after it;
tools/compare.py names the region where the build first differs.

Usage: gen_link.py <ver>
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from buildcache import write_if_changed  # noqa: E402
from c.compile_c import agbcc_prefix  # noqa: E402
from manifest import (  # noqa: E402
    SPLIT_SECTION_DIRECTIVES,
    object_path,
    parse_manifest,
    ram_symbols_source,
    read_lib_objects,
    read_ram_addresses,
)

BASE_ADDR = 0x08000000


def write_ram_symbols(ver: str) -> None:
    """Writes the assembly that defines every RAM variable of
    ram_symbols.<ver>.inc as a global symbol, once for the whole link."""
    path = f"ram_symbols.{ver}.inc"
    with open(path) as f:
        names = re.findall(r"^\.set\s+(\w+)\s*,", f.read(), re.M)
    out = [f'.include "{path}"', *(f".global {name}" for name in names)]
    write_if_changed(ram_symbols_source(ver), "\n".join(out) + "\n")


def extract_member(archive: str, member: str, out: str) -> None:
    """Copies one member of agbcc's installed archive to out."""
    path = os.path.join(agbcc_prefix(), "lib", archive)
    run = subprocess.run(["arm-none-eabi-ar", "p", path, member], capture_output=True)
    if run.returncode or not run.stdout:
        sys.exit(f"cannot extract {member} from {path}:\n{run.stderr.decode()}")
    write_if_changed(out, run.stdout)


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    regions, labels = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    ram_addresses = read_ram_addresses(f"regions.{ver}.txt")
    names = {name for _, name in regions}
    objects = {name: object_path(ver, source) for source, name in regions}

    for name, (archive, member, _) in lib_objects.items():
        extract_member(archive, member, objects[name])
    write_ram_symbols(ver)

    # placements, in link order: (output section, object, input section,
    # region name)
    placements = []
    for i, (_, name) in enumerate(regions):
        section = next((s for s in SPLIT_SECTION_DIRECTIVES.values()
                        if name.endswith(s) and name[:-len(s)] in names), ".text")
        placements.append((f".rgn{i:03d}", objects[name], section, name))

    with open(f"build/{ver}/link.ld", "w") as f:
        f.write(f"INPUT({object_path(ver, ram_symbols_source(ver))})\n")
        f.write("SECTIONS\n{\n")
        # The game's own RAM variables are fixed addresses
        # (ram_symbols.<ver>.inc); a library object's .bss is placed where
        # the ROM's references to it point. These come first, so the
        # location counter only ever moves forward.
        for i, (name, (_, _, bss)) in enumerate(sorted(lib_objects.items())):
            if bss is not None:
                f.write(f"    .libbss{i:03d} {hex(bss)} (NOLOAD) : "
                        f"{{ {objects[name]}(.bss) }}\n")
        f.write(f"    . = {hex(BASE_ADDR)};\n")
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

    print(f"{ver}: {len(regions)} regions -> {len(placements)} placed sections")


if __name__ == "__main__":
    main()
