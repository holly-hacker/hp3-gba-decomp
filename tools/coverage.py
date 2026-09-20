#!/usr/bin/env python3
"""Report how much of the ROM the manifest has claimed, by area and kind.

Reads regions.<ver>.txt and buckets every region-bearing row into:
  c-file  -- compiled C (matched decompilation / reconstructed tables)
  asm-file -- committed hand assembly
  data    -- extracted-asset directives (krawall, dialog-text, ...)
  raw     -- unclaimed, filled from the baserom with .incbin
"matched" is c-file + asm-file + data, i.e. everything that is not raw.

Each area (code 1, data, code 2) is measured by the bytes of each kind that
fall inside it; a region straddling an area boundary is split at the boundary.
"""
import argparse
import sys

# Area boundaries for the US ROM: [start, end) each.
US_AREAS = [
    ("code (start)", 0x08000000, 0x0804BDBC),
    ("data", 0x0804BDBC, 0x08F9FBF6),
    ("code (end)", 0x08F9FBF6, 0x08FB4B40),
]

KINDS = ["c-file", "asm-file", "data", "raw"]
COLUMNS = ["c-file", "asm-file", "data", "matched", "raw"]
NON_REGION = {"label", "thumb-func"}


def kind_of(directive: str) -> str:
    if directive == "c-file":
        return "c-file"
    if directive == "asm-file":
        return "asm-file"
    return "data"


def read_regions(path: str) -> list[tuple[int, int, str, str]]:
    """Returns sorted (start, end, kind, name) for every region row."""
    out = []
    with open(path) as f:
        for lineno, raw in enumerate(f, 1):
            parts = raw.split("#", 1)[0].split()
            if not parts or parts[0] in NON_REGION:
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


AREA_W, RANGE_W, BYTES_W, PCT_W = 13, 17, 10, 6


def fmt_row(label: str, span: str, total: int, sizes: dict[str, int]) -> str:
    sizes = {**sizes, "matched": total - sizes["raw"]}
    cells = "  ".join(
        f"{sizes[k]:>{BYTES_W},} {100 * sizes[k] / total:>{PCT_W - 1}.1f}%"
        for k in COLUMNS
    )
    return f"{label:<{AREA_W}}  {span:<{RANGE_W}}  {total:>{BYTES_W},}  {cells}"


def fmt_header() -> str:
    cell_w = BYTES_W + 1 + PCT_W
    cells = "  ".join(f"{k:>{cell_w}}" for k in COLUMNS)
    return f"{'area':<{AREA_W}}  {'range':<{RANGE_W}}  {'bytes':>{BYTES_W}}  {cells}"


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("ver", nargs="?", default="us")
    ap.add_argument(
        "--area",
        action="append",
        metavar="NAME:START:END",
        help="override the default US areas (hex addresses); repeatable",
    )
    ap.add_argument("--list-raw", action="store_true",
                    help="also list the largest unclaimed gaps in each area")
    args = ap.parse_args()

    areas = US_AREAS
    if args.area:
        areas = []
        for spec in args.area:
            name, s, e = spec.split(":")
            areas.append((name, int(s, 16), int(e, 16)))
    elif args.ver != "us":
        sys.exit("default areas are US-only; pass --area NAME:START:END")

    regions = read_regions(f"regions.{args.ver}.txt")

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


if __name__ == "__main__":
    main()
