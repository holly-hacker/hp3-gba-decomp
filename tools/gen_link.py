#!/usr/bin/env python3
"""Turn regions.<ver>.txt into one object per region plus a linker script.

Writes, all under build/<ver>/ and none of it committed:

  obj/<name>.s        a wrapper per region: the assembler prelude, then an
                      .include (or .incbin) of the region's real source
  obj/gaps.s          every unclaimed byte range, one section per gap,
                      .incbin straight from the baserom
  obj/<name>.o        a lib-object row's member, extracted unchanged from
                      agbcc's installed archive
  link.ld             places those sections one after another, in manifest
                      order, each at its own alignment

Every section is followed by an ASSERT that it starts at its manifest
address, so a region that assembles to the wrong size fails the link at the
first region it moves. Without the ASSERTs, the same script links a ROM in
which everything after a resized region has moved.

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
    Labels,
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
        f'.include "ram_symbols.{ver}.inc"',
        ".text",
    ]


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
    start, end, srcfile, name = region
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
    _, _, srcfile, name = region
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


def write_gaps(objdir: str, ver: str, gaps: list, labels: Labels) -> list[str]:
    """Writes one section per unclaimed range, with any declared labels
    defined inside it so extracted code can reference raw territory."""
    rom = f"baserom.{ver}.gba"
    out = [".syntax unified", '.include "macros.inc"']
    names = []
    for i, (start, end) in enumerate(gaps):
        section = f".gap{i:03d}"
        names.append(section)
        out.append(f'.section {section}, "ax"')
        cur = start
        for point in sorted(a for a in labels if start <= a < end):
            if point > cur:
                out.append(f'.incbin "{rom}", {hex(cur - BASE_ADDR)}, {hex(point - cur)}')
            name, is_thumb = labels[point]
            if is_thumb:
                out.append(f"thumb_func_label {name}")
            else:
                out.append(f".global {name}")
            out.append(f"{name}:")
            cur = point
        if cur < end:
            out.append(f'.incbin "{rom}", {hex(cur - BASE_ADDR)}, {hex(end - cur)}')
    write_if_changed(os.path.join(objdir, "gaps.s"), "\n".join(out) + "\n")
    return names


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    rom_size = os.path.getsize(f"baserom.{ver}.gba")
    regions, labels = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    sectioned = read_placements(f"regions.{ver}.txt")

    objdir = f"build/{ver}/obj"
    os.makedirs(objdir, exist_ok=True)

    names = {region[3] for region in regions}
    if len(names) != len(regions) or "gaps" in names:
        sys.exit(f"regions.{ver}.txt: region names must be unique and not 'gaps'")

    # placements: (address, output section, object stem, input section,
    # region name, RAM address or None)
    placements = []
    gaps = []
    addr = BASE_ADDR
    for i, region in enumerate(regions):
        start, end, _, name = region
        if start > addr:
            gaps.append((addr, start))
        addr = end
        if name in sectioned:
            stem, section, vma = sectioned[name]
            if stem == name:
                write_sectioned(objdir, ver, region)
            placements.append((start, f".rgn{i:03d}", stem, section, name, vma))
            continue
        suffix = next((s for s in SPLIT_SECTION_DIRECTIVES.values()
                       if name.endswith(s) and name[:-len(s)] in names), None)
        if suffix is not None:
            placements.append((start, f".rgn{i:03d}", name[:-len(suffix)], suffix, name, None))
            continue
        if name in lib_objects:
            archive, member, _ = lib_objects[name]
            extract_member(objdir, archive, member, name)
            placements.append((start, f".rgn{i:03d}", name, ".text", name, None))
            continue
        split = {s: name + s for s in SPLIT_SECTION_DIRECTIVES.values()
                 if name + s in names}
        write_region(objdir, ver, region, split)
        placements.append((start, f".rgn{i:03d}", name, ".text", name, None))
    if addr < BASE_ADDR + rom_size:
        gaps.append((addr, BASE_ADDR + rom_size))

    gap_sections = write_gaps(objdir, ver, gaps, labels)
    placements += [(g[0], s, "gaps", s, None, None) for g, s in zip(gaps, gap_sections)]
    placements.sort()

    # Objects of regions that no longer exist would otherwise be linked.
    keep = {f"{p[2]}{ext}" for p in placements for ext in (".s", ".o")}
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
        for address, section, stem, input_section, region_name, vma in placements:
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
            f.write(f'    ASSERT(LOADADDR({section}) == {hex(address)}, '
                    f'"{region_name or section} is not at {hex(address)}")\n')
            prev, prev_runs_from_ram = section, vma is not None
        # A label inside a region has no gap to be defined in. Unless the
        # region's own source defines it, it names a ROM address the
        # original link supplied, such as where a RAM image is stored or
        # an empty table that shares the next object's address. It is
        # defined relative to where that region is stored, so it moves
        # with the region.
        for i, (start, end, srcfile, name) in enumerate(regions):
            points = sorted(a for a in labels if start <= a < end)
            if not points:
                continue
            if name in sectioned:
                own = set()
            elif srcfile.endswith(".bin"):
                own = {name}
            else:
                own = set(exported_labels(srcfile))
            for point in points:
                if labels[point][0] not in own:
                    offset = f" + {hex(point - start)}" if point > start else ""
                    f.write(f"    {labels[point][0]} = LOADADDR(.rgn{i:03d}){offset};\n")
        f.write("    /DISCARD/ : { *(.comment) *(.ARM.attributes) *(.note*) }\n")
        # Anything still unplaced is a section of an object that no
        # manifest row places; ld would otherwise put it where it likes.
        f.write("    .unplaced : { *(*) }\n")
        f.write(f'    ASSERT(SIZEOF(.unplaced) == 0, "an object has a section '
                f'that no regions.{ver}.txt row places")\n')
        f.write("}\n")

    print(f"{ver}: {len(regions)} regions + {len(gaps)} gaps -> "
          f"{len(placements)} placed sections")


if __name__ == "__main__":
    main()
