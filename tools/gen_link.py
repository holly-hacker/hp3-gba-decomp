#!/usr/bin/env python3
"""Turn regions.<ver>.txt into one object per region plus a linker script.

Writes, all under build/<ver>/ and none of it committed:

  obj/rNNN_<name>.s   a wrapper per region: the assembler prelude, then an
                      .include (or .incbin) of the region's real source
  obj/gaps.s          every unclaimed byte range, one section per gap,
                      .incbin straight from the baserom
  link.ld             places each of those sections at its manifest address

The linker, not the order of a concatenated file, decides where things
land, so a region that assembles to the wrong size is caught by ld or by
tools/check_sections.py rather than silently shifting its neighbours.

Usage: gen_link.py <ver>
"""
import os
import re
import shutil
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import RODATA_SUFFIX, Labels, parse_manifest  # noqa: E402

BASE_ADDR = 0x08000000


def prelude(ver: str) -> list[str]:
    return [
        ".syntax unified",
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


def write_region(objdir: str, ver: str, idx: int, region,
                 rodata_idx: int | None = None) -> tuple[str, str]:
    """Writes the wrapper .s for one region; returns (section, stem).

    rodata_idx is the index of the region holding this C object's .rodata
    (a c-rodata row); that region's markers bracket the object's .rodata.
    """
    start, end, srcfile, name = region
    stem = f"r{idx:03d}_{name}"
    out = prelude(ver)
    # ld rounds an output section's size up to its alignment, so a region
    # that came out a couple of bytes short still measures full there.
    # These bracket the real content for tools/check_sections.py.
    if rodata_idx is not None:
        out += [".section .rodata", f"__rgn{rodata_idx:03d}_beg:", ".text"]
    out.append(f"__rgn{idx:03d}_beg:")
    if srcfile.endswith(".bin"):
        out += [f".global {name}", f"{name}:", f'.incbin "{srcfile}"']
    else:
        out += [f".global {label}" for label in exported_labels(srcfile)]
        out += [f'.include "{srcfile}"']
    if rodata_idx is not None:
        out += [".section .rodata", f"__rgn{rodata_idx:03d}_end:", ".text"]
    out.append(f"__rgn{idx:03d}_end:")
    with open(os.path.join(objdir, f"{stem}.s"), "w") as f:
        f.write("\n".join(out) + "\n")
    return f".rgn{idx:03d}", stem


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
    with open(os.path.join(objdir, "gaps.s"), "w") as f:
        f.write("\n".join(out) + "\n")
    return names


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    rom_size = os.path.getsize(f"baserom.{ver}.gba")
    regions, labels = parse_manifest(f"regions.{ver}.txt", ver)

    objdir = f"build/{ver}/obj"
    shutil.rmtree(objdir, ignore_errors=True)
    os.makedirs(objdir)

    index = {region[3]: i for i, region in enumerate(regions)}

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
            owner = index[name[:-len(RODATA_SUFFIX)]]
            placements.append((start, f".rgn{i:03d}",
                               f"r{owner:03d}_{regions[owner][3]}", ".rodata"))
            continue
        section, stem = write_region(objdir, ver, i, region,
                                     index.get(name + RODATA_SUFFIX))
        placements.append((start, section, stem, ".text"))
    if addr < BASE_ADDR + rom_size:
        gaps.append((addr, BASE_ADDR + rom_size))

    gap_sections = write_gaps(objdir, ver, gaps, labels)
    placements += [(g[0], s, "gaps", s) for g, s in zip(gaps, gap_sections)]
    placements.sort()

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
