#!/usr/bin/env python3
"""Assemble every build/<ver>/obj/*.s wrapper to its .o, through the build cache.

A wrapper's object depends on its own text and on every file it includes
or incbins, which only the assembler knows, so the cache works in two
steps (tools/buildcache.py):

  as-deps  wrapper text -> the files the last assembly of it read (from
           `as --MD`)
  as       wrapper text + those files' contents -> object bytes

A cached dependency list can only go stale through a change to one of the
listed files, which also changes the second key, so a hit is always the
object the assembler would produce now. Objects do not record the path of
their source, and each is written to obj/<name>.o; the cache never shows
in the linker script or the ELF.

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

AS_FLAGS = ["-mcpu=arm7tdmi"]


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


def assemble(assembler: str, head_salt: str, source: str) -> bool:
    """Writes source's object; returns whether it came from the cache."""
    out = source[:-len(".s")] + ".o"
    head = buildcache.digest(head_salt, Path(source).read_bytes())
    deps = buildcache.load("as-deps", head)
    if deps is not None:
        key = object_key(head, json.loads(deps))
        obj = buildcache.load("as", key) if key else None
        if obj is not None:
            buildcache.write_if_changed(out, obj)
            return True
    with tempfile.TemporaryDirectory() as tmp:
        depfile, objfile = os.path.join(tmp, "deps"), os.path.join(tmp, "obj")
        run = subprocess.run([assembler, *AS_FLAGS, "--MD", depfile, source, "-o", objfile],
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
    head_salt = buildcache.digest(buildcache.tool_digest(), os.path.realpath(assembler), AS_FLAGS)
    sources = sorted(str(p) for p in Path(f"build/{ver}/obj").glob("*.s"))
    with ThreadPoolExecutor(os.cpu_count()) as pool:
        hits = sum(pool.map(lambda s: assemble(assembler, head_salt, s), sources))
    print(f"{ver}: assembled {len(sources) - hits} of {len(sources)} objects "
          f"({hits} from the cache)")


if __name__ == "__main__":
    main()
