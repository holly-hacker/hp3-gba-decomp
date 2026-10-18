#!/usr/bin/env python3
"""Generate Krawall's public krawall.h, as its own build does (genheader.cmake).

The header is genheader.pre, then the part of each exported header between
its `%b` and `//%e` markers, then genheader.post. Game code includes it as
"3rd_party/krawall.h"; it declares the API with Krawall's own minimal types
and, for a GCC 2 compiler such as agbcc, maps the IWRAM functions to their
Thumb stubs (stub.S).

Usage: gen_header.py   (writes build/include/3rd_party/krawall.h)
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from buildcache import write_if_changed  # noqa: E402

HEADERS = "include/3rd_party/krawall"
# genheader.cmake's FILES, in the order Krawall's CMakeLists.txt gives them.
EXPORT_HEADERS = ["general.h", "player.h", "mixer.h", "directsound.h"]
OUTPUT = "build/include/3rd_party/krawall.h"


def public_header() -> str:
    def read(name: str) -> str:
        with open(os.path.join(HEADERS, name)) as f:
            return f.read()

    out = read("genheader.pre")
    for name in EXPORT_HEADERS:
        m = re.fullmatch(r".*%b(.*)//%e.*", read(name), re.S)
        if m is None:
            sys.exit(f"{HEADERS}/{name}: no %b ... //%e section")
        out += m.group(1)
    return out + read("genheader.post")


def write_public_header() -> str:
    """Writes the header if it changed; returns the include directory."""
    write_if_changed(OUTPUT, public_header().encode())
    return os.path.dirname(os.path.dirname(OUTPUT))


if __name__ == "__main__":
    write_public_header()
