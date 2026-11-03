#!/usr/bin/env python3
"""Write build/build.ninja, which builds both versions' ROMs.

Each step is one edge per version, running the existing script over the
whole version: the packers, compile_c.py, gen_link.py and assemble.py. These
keep their own content caches (tools/buildcache.py) and only rewrite files
whose content changed, so they run on every build and the link reruns only
when an object or link.ld changed.

build.ninja reruns this script when a manifest or the script changes.

Usage: configure.py   (then `ninja -f build/build.ninja`)
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import (  # noqa: E402
    object_path,
    parse_manifest,
    ram_symbols_source,
    read_lib_objects,
)

VERSIONS = ["us", "jp"]
NINJA_FILE = "build/build.ninja"

RULES = """\
ninja_required_version = 1.10
builddir = build

rule configure
  command = python3 tools/configure.py
  description = configure
  generator = 1

rule script
  command = python3 $script $ver
  description = $script $ver
  restat = 1

rule link
  command = arm-none-eabi-ld --no-warn-rwx-segments --emit-relocs -T $ldscript -o $elf $
    && arm-none-eabi-objcopy -O binary --pad-to 0x9000000 --gap-fill 0x00 $elf $gba
  description = link $gba

# Never exists, so whatever depends on it always runs.
build always: phony
"""

# The region sources each script writes, by their directory under
# build/<ver>/.
PRODUCERS = {
    "graphics": "tools/graphics/pack_graphics.py",
    "audio": "tools/krawall/pack_krawall.py",
    "text": "tools/text/pack_text.py",
    "c": "tools/c/compile_c.py",
}


def paths(items) -> str:
    return " ".join(sorted(items))


def version_edges(ver: str) -> list[str]:
    regions, _ = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    sources = {source for source, name in regions if name not in lib_objects}
    produced = {script: set() for script in PRODUCERS.values()}
    for source in sources:
        top = source.removeprefix(f"build/{ver}/").split("/")[0]
        if source.startswith(f"build/{ver}/") and top in PRODUCERS:
            produced[PRODUCERS[top]].add(source)

    graphics = produced["tools/graphics/pack_graphics.py"]
    lib_members = {object_path(ver, source) for source, name in regions
                   if name in lib_objects}
    objects = {object_path(ver, source) for source in sources}
    objects.add(object_path(ver, ram_symbols_source(ver)))
    ldscript = f"build/{ver}/link.ld"
    elf, gba = f"build/{ver}/rom.elf", f"build/{ver}/rom.gba"

    def script_edge(script, outputs, after=()):
        order = f" || {paths(after)}" if after else ""
        return (f"build {paths(outputs)}: script | always{order}\n"
                f"  script = {script}\n  ver = {ver}\n")

    return [
        script_edge("tools/graphics/pack_graphics.py", graphics),
        script_edge("tools/krawall/pack_krawall.py",
                    produced["tools/krawall/pack_krawall.py"]),
        script_edge("tools/text/pack_text.py",
                    produced["tools/text/pack_text.py"]),
        # C includes the generated graphics headers.
        script_edge("tools/c/compile_c.py", produced["tools/c/compile_c.py"],
                    after=graphics),
        script_edge("tools/gen_link.py",
                    {ldscript, ram_symbols_source(ver), *lib_members}),
        script_edge("tools/assemble.py", objects,
                    after=set().union(*produced.values(),
                                      {ram_symbols_source(ver)})),
        f"build {elf} {gba}: link {ldscript} {paths(objects | lib_members)}\n"
        f"  ldscript = {ldscript}\n  elf = {elf}\n  gba = {gba}\n",
    ]


def main() -> None:
    edges = [RULES,
             f"build {NINJA_FILE}: configure | tools/configure.py "
             f"tools/manifest.py "
             + " ".join(f"regions.{ver}.txt" for ver in VERSIONS) + "\n"]
    for ver in VERSIONS:
        edges += version_edges(ver)
    edges.append("default " + " ".join(f"build/{ver}/rom.gba" for ver in VERSIONS) + "\n")
    os.makedirs("build", exist_ok=True)
    with open(NINJA_FILE, "w") as f:
        f.write("\n".join(edges))


if __name__ == "__main__":
    main()
