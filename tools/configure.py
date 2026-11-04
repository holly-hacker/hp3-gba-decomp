#!/usr/bin/env python3
"""Write build/build.ninja, which builds both versions' ROMs.

Every C source and every object has its own edge, with the headers and
included files it read recorded through depfiles, so Ninja reruns exactly
the compiles and assemblies whose inputs changed:

  agbcc   cpp -> agbcc -> build/<ver>/c/<name>.s, flags from
          compile_c.profile(), then the section prologue and the trailing
          word alignment every object has
  gcc3    a third-party source, through compile_c.py
  as      a region's source -> its object (manifest.object_path)

The packers and gen_link.py are one edge per version: they run on every
build (their inputs are whole data/ trees) and keep their own content
caches, rewriting only files whose content changed. Two edges write the
headers C includes: Krawall's public header and the graphics headers, which
are the same for every version. The link reruns when an object or link.ld
changed.

build.ninja reruns this script when a manifest, flake.lock or the script
changes.

Usage: configure.py   (then `ninja -f build/build.ninja`)
"""
import glob
import os
import shlex
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from c.compile_c import agbcc_prefix, profile  # noqa: E402
from krawall.gen_header import (  # noqa: E402
    EXPORT_HEADERS,
    HEADERS as KRAWALL_HEADERS,
    OUTPUT as KRAWALL_HEADER,
)
from manifest import (  # noqa: E402
    C_FILE_DIRECTIVES,
    SECTIONED_DIRECTIVES,
    object_path,
    parse_manifest,
    ram_symbols_source,
    read_lib_objects,
    read_rows,
)

VERSIONS = ["us", "jp"]
NINJA_FILE = "build/build.ninja"

# --strip-local-absolute keeps assembler constants (the room-blob macros'
# counters and opcode numbers, defined in every blob) out of the symbols.
# Sources test `.ifdef VERSION_JP` for code that differs on JP.
AS_FLAGS = {"us": "-mcpu=arm7tdmi --strip-local-absolute",
            "jp": "-mcpu=arm7tdmi --strip-local-absolute --defsym VERSION_JP=1"}

# .rodata and .data start word-aligned, as every object's did; the code
# ends padded to 4 bytes with explicit zeros, which is what the ROM has.
PROLOGUE = r"\t.section\t.rodata\n\t.align\t2, 0\n\t.data\n\t.align\t2, 0\n\t.text\n"
EPILOGUE = r"\t.align\t2, 0\n"

RULES = f"""\
ninja_required_version = 1.10
builddir = build

rule configure
  command = python3 tools/configure.py
  description = configure
  generator = 1

rule script
  command = python3 $script $args
  description = $script $args
  restat = 1

rule gcc3
  command = python3 tools/c/compile_c.py $directive $in $out
  description = gcc3 $in
  depfile = $out.d
  deps = gcc

rule krawall_header
  command = python3 tools/krawall/gen_header.py
  description = $out
  restat = 1

rule link
  command = arm-none-eabi-ld --no-warn-rwx-segments --emit-relocs -T $ldscript -o $elf $
    && arm-none-eabi-objcopy -O binary --pad-to 0x9000000 --gap-fill 0x00 $elf $gba
  description = link $gba

# Never exists, so whatever depends on it always runs.
build always: phony

build {KRAWALL_HEADER}: krawall_header tools/krawall/gen_header.py \
{" ".join(f"{KRAWALL_HEADERS}/{name}" for name in
          ["genheader.pre", *EXPORT_HEADERS, "genheader.post"])}
"""

# The region sources each script writes, by their directory under
# build/<ver>/.
PRODUCERS = {
    "graphics": "tools/graphics/pack_graphics.py",
    "audio": "tools/krawall/pack_krawall.py",
    "text": "tools/text/pack_text.py",
}

# c-file directive -> (rule suffix, -O1, ARM).
AGBCC_VARIANTS = {"c-file": ("O2", False, False),
                  "c-file-O1": ("O1", True, False),
                  "c-file-arm": ("arm", False, True)}


def paths(items) -> str:
    return " ".join(sorted(items))


def graphics_yaml() -> list[str]:
    return sorted(glob.glob("graphics/**/*.yaml", recursive=True))


def graphics_headers() -> list[str]:
    return [f"include/gen/graphics/{os.path.splitext(os.path.relpath(path, 'graphics'))[0]}.h"
            for path in graphics_yaml()]


def version_rules(ver: str, prefix: str) -> str:
    out = []
    for suffix, o1, arm in AGBCC_VARIANTS.values():
        cc1, cppflags, cflags = profile("", prefix, o1, ver, arm)
        out.append(
            f"rule agbcc_{ver}_{suffix}\n"
            f"  command = cpp {shlex.join(cppflags)} -MD -MF $out.d -MT $out -o $out.i $in"
            f" && {cc1} {shlex.join(cflags)} -o $out.cc - < $out.i"
            f" && {{ printf '{PROLOGUE}' && cat $out.cc && printf '{EPILOGUE}'; }} > $out"
            f" && rm $out.i $out.cc\n"
            f"  description = agbcc $in\n"
            f"  depfile = $out.d\n"
            f"  deps = gcc\n")
    out.append(
        f"rule as_{ver}\n"
        f"  command = arm-none-eabi-as {AS_FLAGS[ver]} --MD $out.d $in -o $out\n"
        f"  description = as $in\n"
        f"  depfile = $out.d\n"
        f"  deps = gcc\n")
    return "\n".join(out)


def version_edges(ver: str) -> list[str]:
    manifest = f"regions.{ver}.txt"
    regions, _ = parse_manifest(manifest, ver)
    lib_objects = read_lib_objects(manifest)
    sources = {source for source, name in regions if name not in lib_objects}
    sources.add(ram_symbols_source(ver))
    produced = {script: set() for script in PRODUCERS.values()}
    for source in sources:
        top = source.removeprefix(f"build/{ver}/").split("/")[0]
        if source.startswith(f"build/{ver}/") and top in PRODUCERS:
            produced[PRODUCERS[top]].add(source)
    # Each graphics group's .s incbins its .bin.
    graphics = produced["tools/graphics/pack_graphics.py"]
    graphics |= {os.path.splitext(s)[0] + ".bin" for s in set(graphics)}

    lib_members = {object_path(ver, source) for source, name in regions
                   if name in lib_objects}
    objects = {object_path(ver, source): source for source in sources}
    ldscript = f"build/{ver}/link.ld"
    elf, gba = f"build/{ver}/rom.elf", f"build/{ver}/rom.gba"

    def script_edge(script, outputs):
        return (f"build {paths(outputs)}: script | always\n"
                f"  script = {script}\n  args = {ver}\n")

    edges = [script_edge(script, outputs) for script, outputs in produced.items()]
    edges.append(script_edge("tools/gen_link.py",
                             {ldscript, ram_symbols_source(ver), *lib_members}))

    # C includes the generated headers; the depfiles name the ones each
    # file read once it has been compiled.
    headers = "|| generated_headers"
    for _, parts in read_rows(manifest):
        directive = parts[0]
        if directive not in C_FILE_DIRECTIVES:
            continue
        src, name = parts[1:3]
        out = f"build/{ver}/c/{name}.s"
        if directive in SECTIONED_DIRECTIVES:
            edges.append(f"build {out}: gcc3 {src} | tools/c/compile_c.py {headers}\n"
                         f"  directive = {directive}\n")
        else:
            rule = f"agbcc_{ver}_{AGBCC_VARIANTS[directive][0]}"
            edges.append(f"build {out}: {rule} {src} {headers}\n")

    for obj, source in sorted(objects.items()):
        edges.append(f"build {obj}: as_{ver} {source}\n")

    edges.append(
        f"build {elf} {gba}: link {ldscript} {paths(set(objects) | lib_members)}\n"
        f"  ldscript = {ldscript}\n  elf = {elf}\n  gba = {gba}\n")
    return edges


def main() -> None:
    prefix = agbcc_prefix()
    edges = [RULES,
             f"build {NINJA_FILE}: configure | tools/configure.py "
             f"tools/manifest.py tools/c/compile_c.py flake.lock "
             + " ".join(f"regions.{ver}.txt" for ver in VERSIONS) + "\n",
             f"build {' '.join(graphics_headers())}: script | always\n"
             f"  script = tools/graphics/pack_graphics.py\n  args = headers\n",
             f"build generated_headers: phony {KRAWALL_HEADER} "
             + " ".join(graphics_headers()) + "\n"]
    for ver in VERSIONS:
        edges.append(version_rules(ver, prefix))
        edges += version_edges(ver)
    edges.append("default " + " ".join(f"build/{ver}/rom.gba" for ver in VERSIONS) + "\n")
    os.makedirs("build", exist_ok=True)
    with open(NINJA_FILE, "w") as f:
        f.write("\n".join(edges))


if __name__ == "__main__":
    main()
