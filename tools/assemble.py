#!/usr/bin/env python3
"""Assemble every source of regions.<ver>.txt to its object under
build/<ver>/obj/ (manifest.object_path), through the build cache.

An object depends on its source and on every file the source includes or
incbins, which only the assembler knows, so the cache works in two steps
(tools/buildcache.py):

  as-deps  source -> the files the last assembly of it read (from
           `as --MD`)
  as       source + those files' contents -> object bytes

A cached dependency list can only go stale through a change to one of the
listed files, which also changes the second key, so a hit is always the
object the assembler would produce now. Objects do not record the path of
their source; the cache never shows in the linker script or the ELF.

Usage: assemble.py <ver>   (after `gen-link`)
"""
import json
import os
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import buildcache  # noqa: E402
from manifest import (  # noqa: E402
    object_path,
    parse_manifest,
    ram_symbols_source,
    read_lib_objects,
)

# --strip-local-absolute keeps assembler constants (the room-blob macros'
# counters and opcode numbers, defined in every blob) out of the symbols.
AS_FLAGS = ["-mcpu=arm7tdmi", "--strip-local-absolute"]


def as_flags(ver: str) -> list[str]:
    """Sources test `.ifdef VERSION_JP` for code that differs on JP."""
    return AS_FLAGS + (["--defsym", "VERSION_JP=1"] if ver == "jp" else [])


def read_deps(depfile: str, source: str) -> list[str]:
    """Prerequisites from an `as --MD` makefile rule, minus the source."""
    text = Path(depfile).read_text().replace("\\\n", " ")
    deps = text.split(":", 1)[1].split()
    return sorted({os.path.relpath(d) for d in deps} - {os.path.relpath(source)})


def object_key(head: str, deps: list[str]) -> str | None:
    try:
        return buildcache.digest(head, [(d, buildcache.file_digest(d)) for d in deps])
    except FileNotFoundError:
        return None


def assemble(assembler: str, flags: list[str], head_salt: str, source: str,
             out: str) -> bool:
    """Writes source's object to out; returns whether it came from the cache."""
    head = buildcache.digest(head_salt, source, Path(source).read_bytes())
    deps = buildcache.load("as-deps", head)
    if deps is not None:
        key = object_key(head, json.loads(deps))
        obj = buildcache.load("as", key) if key else None
        if obj is not None:
            buildcache.write_if_changed(out, obj)
            return True
    with tempfile.TemporaryDirectory() as tmp:
        depfile, objfile = os.path.join(tmp, "deps"), os.path.join(tmp, "obj")
        run = subprocess.run([assembler, *flags, "--MD", depfile, source, "-o", objfile],
                             capture_output=True, text=True)
        if run.returncode:
            sys.exit(f"as failed on {source}:\n{run.stderr}")
        deps = read_deps(depfile, source)
        obj = Path(objfile).read_bytes()
    buildcache.store("as-deps", head, json.dumps(deps).encode())
    buildcache.store("as", object_key(head, deps), obj)
    buildcache.write_if_changed(out, obj)
    return False


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]
    assembler = shutil.which("arm-none-eabi-as")
    if assembler is None:
        sys.exit("arm-none-eabi-as not found -- are you in `nix develop`?")
    flags = as_flags(ver)
    head_salt = buildcache.digest(buildcache.tool_digest(), os.path.realpath(assembler), flags)
    regions, _ = parse_manifest(f"regions.{ver}.txt", ver)
    lib_objects = read_lib_objects(f"regions.{ver}.txt")
    sources = {source for source, name in regions if name not in lib_objects}
    sources.add(ram_symbols_source(ver))
    jobs = [(source, object_path(ver, source)) for source in sorted(sources)]
    with ThreadPoolExecutor(os.cpu_count()) as pool:
        hits = sum(pool.map(lambda job: assemble(assembler, flags, head_salt, *job), jobs))
    print(f"{ver}: assembled {len(jobs) - hits} of {len(jobs)} objects "
          f"({hits} from the cache)")


if __name__ == "__main__":
    main()
