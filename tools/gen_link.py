#!/usr/bin/env python3
"""Turn regions.<ver>.txt into one object per region plus a linker script.

Writes, all under build/<ver>/ and none of it committed:

  obj/<name>.s        a wrapper per region: the assembler prelude, then an
                      .include (or .incbin) of the region's real source
  obj/<name>.o        a lib-object row's member, extracted unchanged from
                      agbcc's installed archive
  link.ld             places those sections one after another, in manifest
                      order, each at its own alignment

A region that assembles to a different size moves everything after it;
tools/compare.py names the region where the build first differs.

Wrappers are named after their region, not its position, and unchanged
ones are left alone, so inserting a manifest row changes no other wrapper
and tools/assemble.py reuses their objects.

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
    parse_manifest,
    read_lib_objects,
    read_placements,
)

BASE_ADDR = 0x08000000


def prelude(ver: str) -> list[str]:
    version = [".set VERSION_JP, 1"] if ver == "jp" else []
    return [
        ".syntax unified",
        *version,
        '.include "macros.inc"',
        ".text",
    ]


def write_ram_symbols(objdir: str, ver: str) -> None:
    """Writes obj/ram_symbols.s, which defines every RAM variable of
    ram_symbols.<ver>.inc as a global symbol, once for the whole link."""
    path = f"ram_symbols.{ver}.inc"
    with open(path) as f:
        names = re.findall(r"^\.set\s+(\w+)\s*,", f.read(), re.M)
    out = [f'.include "{path}"', *(f".global {name}" for name in names)]
    write_if_changed(os.path.join(objdir, "ram_symbols.s"), "\n".join(out) + "\n")


def exported_labels(srcfile: str) -> list[str]:
    """Every top-level label a region source defines.

    Regions used to share one assembly unit, where each label was visible
    to all the others without saying so. Objects don't work that way, so
    the wrapper re-exports them to keep cross-region references (a table
    of pointers to tables, say) resolving as before. Labels the assembler
    treats as local (.L...) are left alone.
    """
    with open(srcfile) as f:
        return re.findall(r"^([A-Za-z_][A-Za-z0-9_]*):", f.read(), re.M)


def write_region(objdir: str, ver: str, region,
                 split: dict[str, str] | None = None) -> None:
    """Writes the wrapper .s for one region, named after it.

    split maps each section of this C object that a row of its own places
    (.rodata for c-rodata, .data for c-data) to that row's region, whose
    markers bracket the section.
    """
    split = split or {}
    srcfile, name = region
    out = prelude(ver)
    # These bracket the region's content in the linked ELF.
    for section, region_name in split.items():
        out += [f".section {section}", f"__rgn_{region_name}_beg:", ".text"]
    out.append(f"__rgn_{name}_beg:")
    if srcfile.endswith(".bin"):
        out += [f".global {name}", f"{name}:", f'.incbin "{srcfile}"']
    else:
        out += [f".global {label}" for label in exported_labels(srcfile)]
        out += [f'.include "{srcfile}"']
    for section, region_name in split.items():
        out += [f".section {section}", f"__rgn_{region_name}_end:", ".text"]
    out.append(f"__rgn_{name}_end:")
    write_if_changed(os.path.join(objdir, f"{name}.s"), "\n".join(out) + "\n")


def write_sectioned(objdir: str, ver: str, region) -> None:
    """Writes the wrapper .s for a sectioned object (c-file-gcc3 and
    friends). Its sections go to several places, some of them run from
    RAM, so link.ld brackets each one instead of the wrapper."""
    srcfile, name = region
    out = prelude(ver)
    out += [f".global {label}" for label in exported_labels(srcfile)]
    out += [f'.include "{srcfile}"']
    write_if_changed(os.path.join(objdir, f"{name}.s"), "\n".join(out) + "\n")


def extract_member(objdir: str, archive: str, member: str, name: str) -> None:
    """Copies one member of agbcc's installed archive to obj/<name>.o."""
    path = os.path.join(agbcc_prefix(), "lib", archive)
    run = subprocess.run(["arm-none-eabi-ar", "p", path, member], capture_output=True)
    if run.returncode or not run.stdout:
        sys.exit(f"cannot extract {member} from {path}:\n{run.stderr.decode()}")
    write_if_changed(os.path.join(objdir, f"{name}.o"), run.stdout)


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    regions, labels = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    sectioned = read_placements(f"regions.{ver}.txt")

    objdir = f"build/{ver}/obj"
    os.makedirs(objdir, exist_ok=True)

    names = {name for _, name in regions}

    # placements, in link order: (output section, object stem, input
    # section, region name, RAM address or None)
    placements = []
    for i, region in enumerate(regions):
        name = region[1]
        if name in sectioned:
            stem, section, vma = sectioned[name]
            if stem == name:
                write_sectioned(objdir, ver, region)
            placements.append((f".rgn{i:03d}", stem, section, name, vma))
            continue
        suffix = next((s for s in SPLIT_SECTION_DIRECTIVES.values()
                       if name.endswith(s) and name[:-len(s)] in names), None)
        if suffix is not None:
            placements.append((f".rgn{i:03d}", name[:-len(suffix)], suffix, name, None))
            continue
        if name in lib_objects:
            archive, member, _ = lib_objects[name]
            extract_member(objdir, archive, member, name)
            placements.append((f".rgn{i:03d}", name, ".text", name, None))
            continue
        split = {s: name + s for s in SPLIT_SECTION_DIRECTIVES.values()
                 if name + s in names}
        write_region(objdir, ver, region, split)
        placements.append((f".rgn{i:03d}", name, ".text", name, None))

    write_ram_symbols(objdir, ver)

    # Objects of regions that no longer exist would otherwise be linked. A
    # library object has no wrapper to assemble over it.
    keep = {f"{stem}{ext}" for stem in [p[1] for p in placements] + ["ram_symbols"]
            for ext in ((".o",) if stem in lib_objects else (".s", ".o"))}
    for entry in os.listdir(objdir):
        if entry not in keep:
            os.remove(os.path.join(objdir, entry))

    with open(f"build/{ver}/link.ld", "w") as f:
        f.write("SECTIONS\n{\n")
        # The game's own RAM variables are fixed addresses
        # (ram_symbols.<ver>.inc); a library object's .bss is placed where
        # the ROM's references to it point. These come first, so the
        # location counter only ever moves forward.
        for i, (stem, (_, _, bss)) in enumerate(sorted(lib_objects.items())):
            if bss is not None:
                f.write(f"    .libbss{i:03d} {hex(bss)} (NOLOAD) : "
                        f"{{ {objdir}/{stem}.o(.bss) }}\n")
        f.write(f"    . = {hex(BASE_ADDR)};\n")
        prev, prev_runs_from_ram = None, False
        for section, stem, input_section, region_name, vma in placements:
            contents = f"{objdir}/{stem}.o({input_section})"
            if stem in lib_objects or region_name in sectioned:
                # Neither a library object nor a sectioned one has a
                # wrapper that brackets the content.
                contents = (f'"__rgn_{region_name}_beg" = .; {contents} '
                            f'"__rgn_{region_name}_end" = .;')
            # Each section is stored right after the previous one, at its
            # own alignment. A section that runs from RAM is linked at its
            # RAM address, which leaves the location counter there, so the
            # next ROM section restarts it from where that one is stored and
            # states that it is stored where it runs: ld would otherwise
            # keep the RAM section's offset between the two.
            if vma is None and prev_runs_from_ram:
                f.write(f"    . = LOADADDR({prev}) + SIZEOF({prev});\n")
                f.write(f"    {section} : AT(ADDR({section})) {{ {contents} }}\n")
            elif vma is None:
                f.write(f"    {section} : {{ {contents} }}\n")
            else:
                stored = f"ALIGN(LOADADDR({prev}) + SIZEOF({prev}), ALIGNOF({section}))"
                f.write(f"    {section} {hex(vma)} : AT({stored}) {{ {contents} }}\n")
            prev, prev_runs_from_ram = section, vma is not None
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
