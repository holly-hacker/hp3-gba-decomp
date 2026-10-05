#!/usr/bin/env python3
"""Turn regions.<ver>.txt into one object per region plus a linker script.

Writes, all under build/<ver>/ and none of it committed:

  obj/<name>.s        a wrapper per region: the assembler prelude, then an
                      .include (or .incbin) of the region's real source
  obj/gaps.s          every unclaimed byte range, one section per gap,
                      .incbin straight from the baserom
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
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from buildcache import write_if_changed  # noqa: E402
from manifest import RODATA_SUFFIX, Labels, parse_manifest  # noqa: E402

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

    objdir = f"build/{ver}/obj"
    os.makedirs(objdir, exist_ok=True)

    names = {region[3] for region in regions}
    if len(names) != len(regions) or "gaps" in names:
        sys.exit(f"regions.{ver}.txt: region names must be unique and not 'gaps'")

    # placements: (address, output section, object stem, input section)
    placements = []
    gaps = []
    addr = BASE_ADDR
    for i, region in enumerate(regions):
        start, end, _, name = region
        if start > addr:
            gaps.append((addr, start))
        addr = end
        if name.endswith(RODATA_SUFFIX):
            placements.append((start, f".rgn{i:03d}", name[:-len(RODATA_SUFFIX)], ".rodata"))
            continue
        rodata = name + RODATA_SUFFIX
        write_region(objdir, ver, region, rodata if rodata in names else None)
        placements.append((start, f".rgn{i:03d}", name, ".text"))
    if addr < BASE_ADDR + rom_size:
        gaps.append((addr, BASE_ADDR + rom_size))

    gap_sections = write_gaps(objdir, ver, gaps, labels)
    placements += [(g[0], s, "gaps", s) for g, s in zip(gaps, gap_sections)]
    placements.sort()

    # Objects of regions that no longer exist would otherwise be linked.
    keep = {f"{stem}{ext}" for _, _, stem, _ in placements for ext in (".s", ".o")}
    for entry in os.listdir(objdir):
        if entry not in keep:
            os.remove(os.path.join(objdir, entry))

    with open(f"build/{ver}/link.ld", "w") as f:
        f.write("SECTIONS\n{\n")
        for address, section, stem, input_section in placements:
            # SUBALIGN(1): a compiled region's .text carries a 4-byte
            # section-alignment attribute (from compile_c.py's trailing
            # `.align 2, 0`) even when it adds no actual padding. Without
            # this, ld pads its LMA to that alignment for overlap checking
            # and falsely reports it overlapping the next region whenever
            # its real ROM address isn't itself 4-aligned.
            f.write(f"    {section} {hex(address)} : SUBALIGN(1) "
                    f"{{ {objdir}/{stem}.o({input_section}) }}\n")
        f.write("    /DISCARD/ : { *(.comment) *(.ARM.attributes) *(.note*) }\n")
        f.write("}\n")

    print(f"{ver}: {len(regions)} regions + {len(gaps)} gaps -> "
          f"{len(placements)} placed sections")


if __name__ == "__main__":
    main()
