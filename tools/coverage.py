#!/usr/bin/env python3
"""Report how much of the ROM the manifest has claimed, by area and kind.

Reads regions.<ver>.txt and buckets every region-bearing row into:
  c-file  -- compiled C (c-file, c-file-O1 and c-rodata directives)
  asm-file -- committed hand assembly
  data    -- extracted-asset directives (krawall, dialog-text, ...)
  raw     -- unclaimed, filled from the baserom with .incbin
"matched" is c-file + asm-file + data, i.e. everything that is not raw.

Each area (code 1, data, code 2), and with --blocks each code block, is
measured by the bytes of each kind that fall inside it; a region straddling a
boundary is split at it. Areas and blocks come from tools/rom_layout.json.
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import rom_layout  # noqa: E402
from manifest import read_rows  # noqa: E402

KINDS = ["c-file", "asm-file", "data", "raw"]
COLUMNS = ["c-file", "asm-file", "data", "matched", "raw"]
NON_REGION = {"label", "thumb-func", "arm-func"}


def kind_of(directive: str) -> str:
    if directive in {"c-file", "c-file-O1", "c-rodata"}:
        return "c-file"
    if directive == "asm-file":
        return "asm-file"
    return "data"


def read_regions(path: str) -> list[tuple[int, int, str, str]]:
    """Returns sorted (start, end, kind, name) for every region row."""
    out = []
    for lineno, parts in read_rows(path):
        if parts[0] in NON_REGION:
            continue
        try:
            start, end = int(parts[1], 16), int(parts[2], 16)
        except (IndexError, ValueError):
            sys.exit(f"{path}:{lineno}: cannot parse region row")
        out.append((start, end, kind_of(parts[0]), parts[-1]))
    out.sort()
    for a, b in zip(out, out[1:]):
        if b[0] < a[1]:
            sys.exit(f"overlapping regions: {a} and {b}")
    return out


def measure(regions, lo: int, hi: int) -> dict[str, int]:
    sizes = {k: 0 for k in KINDS}
    for start, end, kind, _ in regions:
        overlap = min(end, hi) - max(start, lo)
        if overlap > 0:
            sizes[kind] += overlap
    sizes["raw"] = (hi - lo) - sum(sizes[k] for k in KINDS if k != "raw")
    return sizes


AREA_W, RANGE_W, BYTES_W, PCT_W = 14, 17, 10, 6


def fmt_row(label: str, span: str, total: int, sizes: dict[str, int],
            label_w: int = AREA_W) -> str:
    sizes = {**sizes, "matched": total - sizes["raw"]}
    cells = "  ".join(
        f"{sizes[k]:>{BYTES_W},} {100 * sizes[k] / total:>{PCT_W - 1}.1f}%"
        for k in COLUMNS
    )
    return f"{label:<{label_w}}  {span:<{RANGE_W}}  {total:>{BYTES_W},}  {cells}"


def fmt_header(label: str = "area", label_w: int = AREA_W) -> str:
    cell_w = BYTES_W + 1 + PCT_W
    cells = "  ".join(f"{k:>{cell_w}}" for k in COLUMNS)
    return f"{label:<{label_w}}  {'range':<{RANGE_W}}  {'bytes':>{BYTES_W}}  {cells}"


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("ver", nargs="?", default="us")
    ap.add_argument(
        "--area",
        action="append",
        metavar="NAME:START:END",
        help="override the default areas (hex addresses); repeatable",
    )
    ap.add_argument("--blocks", action="store_true",
                    help="also break the code areas down by block")
    ap.add_argument("--list-raw", action="store_true",
                    help="also list the largest unclaimed gaps in each area")
    args = ap.parse_args()

    for ver in ["us", "jp"]:
        layout_areas, blocks = rom_layout.load(ver)
        areas = [(a.name, a.start, a.end) for a in layout_areas]
        if args.area:
            areas = []
            for spec in args.area:
                name, s, e = spec.split(":")
                areas.append((name, int(s, 16), int(e, 16)))

        regions = read_regions(f"regions.{ver}.txt")

        print(fmt_header())
        total = {k: 0 for k in KINDS}
        span = 0
        for name, lo, hi in areas:
            sizes = measure(regions, lo, hi)
            print(fmt_row(name, f"{lo:08X}-{hi:08X}", hi - lo, sizes))
            for k in KINDS:
                total[k] += sizes[k]
            span += hi - lo
        print(fmt_row("total", "", span, total))

        if args.blocks:
            label_w = max(len(b.name) for b in blocks)
            print()
            print(fmt_header("block", label_w))
            for b in blocks:
                print(fmt_row(b.name, f"{b.start:08X}-{b.end:08X}", b.end - b.start,
                              measure(regions, b.start, b.end), label_w))

        if args.list_raw:
            for name, lo, hi in areas:
                gaps, cur = [], lo
                for start, end, _, _ in regions:
                    if end <= lo or start >= hi:
                        continue
                    if start > cur:
                        gaps.append((start - cur, cur, start))
                    cur = max(cur, end)
                if cur < hi:
                    gaps.append((hi - cur, cur, hi))
                gaps.sort(reverse=True)
                print(f"\nlargest raw gaps in {name}:")
                for size, s, e in gaps[:10]:
                    print(f"  {s:08X}-{e:08X} {size:>9,}")

        print()


if __name__ == "__main__":
    main()
