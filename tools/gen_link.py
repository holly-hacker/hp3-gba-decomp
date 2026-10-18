#!/usr/bin/env python3
"""Turn regions.<ver>.txt into one object per region plus a linker script.

Writes, all under build/<ver>/ and none of it committed:

  obj/<name>.s        a wrapper per region: the assembler prelude, then an
                      .include (or .incbin) of the region's real source
  obj/gaps.s          every unclaimed byte range, one section per gap,
                      .incbin straight from the baserom
  obj/<name>.o        a lib-object row's member, extracted unchanged from
                      agbcc's installed archive
  link.ld             places each of those sections at its manifest address

The linker, not the order of a concatenated file, decides where things
land, so a region that assembles to the wrong size is caught by ld or by
tools/check_sections.py rather than silently shifting its neighbours.

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
    RODATA_SUFFIX,
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


def write_region(objdir: str, ver: str, region, rodata: str | None = None) -> None:
    """Writes the wrapper .s for one region, named after it.

    rodata names the region holding this C object's .rodata (a c-rodata
    row); that region's markers bracket the object's .rodata.
    """
    start, end, srcfile, name = region
    out = prelude(ver)
    # ld rounds an output section's size up to its alignment, so a region
    # that came out a couple of bytes short still measures full there.
    # These bracket the real content for tools/check_sections.py.
    if rodata is not None:
        out += [".section .rodata", f"__rgn_{rodata}_beg:", ".text"]
    out.append(f"__rgn_{name}_beg:")
    if srcfile.endswith(".bin"):
        out += [f".global {name}", f"{name}:", f'.incbin "{srcfile}"']
    else:
        out += [f".global {label}" for label in exported_labels(srcfile)]
        out += [f'.include "{srcfile}"']
    if rodata is not None:
        out += [".section .rodata", f"__rgn_{rodata}_end:", ".text"]
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
        if name.endswith(RODATA_SUFFIX):
            placements.append((start, f".rgn{i:03d}", name[:-len(RODATA_SUFFIX)], ".rodata", name, None))
            continue
        if name in lib_objects:
            archive, member, _ = lib_objects[name]
            extract_member(objdir, archive, member, name)
            placements.append((start, f".rgn{i:03d}", name, ".text", name, None))
            continue
        rodata = name + RODATA_SUFFIX
        write_region(objdir, ver, region, rodata if rodata in names else None)
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
        for address, section, stem, input_section, region_name, vma in placements:
            # SUBALIGN(1): a compiled region's .text carries a 4-byte
            # section-alignment attribute (from compile_c.py's trailing
            # `.align 2, 0`) even when it adds no actual padding. Without
            # this, ld pads its LMA to that alignment for overlap checking
            # and falsely reports it overlapping the next region whenever
            # its real ROM address isn't itself 4-aligned.
            contents = f"{objdir}/{stem}.o({input_section})"
            if stem in lib_objects or region_name in sectioned:
                # Neither a library object nor a sectioned one has a
                # wrapper that brackets the content.
                contents = (f'"__rgn_{region_name}_beg" = .; {contents} '
                            f'"__rgn_{region_name}_end" = .;')
            # A section that runs from RAM is linked at its RAM address
            # and stored at its ROM one. Every section states where it is
            # stored: ld would otherwise give the sections after one that
            # runs from RAM that one's offset between the two.
            run = hex(address if vma is None else vma)
            f.write(f"    {section} {run} : AT({hex(address)}) SUBALIGN(1) {{ {contents} }}\n")
        # The game's own RAM variables are fixed addresses
        # (ram_symbols.<ver>.inc); a library object's .bss is placed where
        # the ROM's references to it point.
        for i, (stem, (_, _, bss)) in enumerate(sorted(lib_objects.items())):
            if bss is not None:
                f.write(f"    .libbss{i:03d} {hex(bss)} (NOLOAD) : "
                        f"{{ {objdir}/{stem}.o(.bss) }}\n")
        # A label inside a sectioned object's region has no gap to be
        # defined in; it names a ROM address the original link script
        # supplied, such as where a RAM image is stored.
        for start, end, _, name in regions:
            if name in sectioned:
                for point in sorted(a for a in labels if start <= a < end):
                    f.write(f"    {labels[point][0]} = {hex(point)};\n")
        f.write("    /DISCARD/ : { *(.comment) *(.ARM.attributes) *(.note*) }\n")
        f.write("}\n")

    print(f"{ver}: {len(regions)} regions + {len(gaps)} gaps -> "
          f"{len(placements)} placed sections")


if __name__ == "__main__":
    main()
