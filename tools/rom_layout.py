#!/usr/bin/env python3
"""Load tools/rom_layout.json: the ROM's areas and its code blocks.

Areas split each ROM into code and data ranges; each area ends where the
next starts, the last at `end`. Blocks are contiguous, named runs of
code (one subsystem or screen each) that tile the code areas; a block ends
where the next one starts, or at the end of its area. Every entry carries a
`us` and `jp` address. Both are analysis-only groupings for tools such as
coverage.py and progress_report.py, not build inputs.
"""
import json
import os
from dataclasses import dataclass

LAYOUT_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rom_layout.json")
DEFAULT_CATEGORY = "game"


@dataclass(frozen=True)
class Area:
    name: str
    start: int
    end: int

    @property
    def is_code(self) -> bool:
        return self.name.startswith("code")


@dataclass(frozen=True)
class Block:
    name: str
    start: int
    end: int
    category: str


def load(ver: str) -> tuple[list[Area], list[Block]]:
    """Returns the areas and blocks of `ver`, sorted by address."""
    with open(LAYOUT_PATH) as f:
        layout = json.load(f)
    starts = [int(a[ver], 16) for a in layout["areas"]]
    ends = starts[1:] + [int(layout["end"][ver], 16)]
    areas = [Area(a["name"], s, e) for a, s, e in zip(layout["areas"], starts, ends)]

    starts = [(int(b[ver], 16), b["name"], b.get("category", DEFAULT_CATEGORY))
              for b in layout["blocks"]]
    if starts != sorted(starts):
        raise ValueError(f"{ver}: blocks are not sorted by address")
    blocks = []
    for area in (a for a in areas if a.is_code):
        inside = [s for s in starts if area.start <= s[0] < area.end]
        if not inside or inside[0][0] != area.start:
            raise ValueError(f"{ver}: no block starts at code area {area.name!r}")
        ends = [s[0] for s in inside[1:]] + [area.end]
        blocks += [Block(name, start, end, cat)
                   for (start, name, cat), end in zip(inside, ends)]
    if len(blocks) != len(starts):
        raise ValueError(f"{ver}: a block starts outside the code areas")
    return areas, blocks
