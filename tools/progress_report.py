#!/usr/bin/env python3
"""Write an objdiff-format progress report for decomp.dev from regions.<ver>.txt.

The report follows objdiff's report.proto (version 2), as JSON. It is
derived from the manifest alone, without building: every c-file row is
byte-exact because the build compares against the baserom.

Units are the manifest's region rows plus one auto-generated unit per
unclaimed gap, split at the area boundaries in coverage.py so each unit is
all code or all data. A unit counts as matched (and complete) when it is
compiled C (c-file, c-file-O1, c-rodata) or, in a data area, an asm-file
row or extracted asset directive. asm-file rows in a code area and
unclaimed gaps count as unmatched.
Function measures are left at zero: the manifest does not record function
boundaries.

Progress categories: `krawall` for the Krawall areas, `libc` for rows whose
source is under src/libc/, `game` for everything else.
"""
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coverage import JP_AREAS, US_AREAS  # noqa: E402
from manifest import (  # noqa: E402
    ASM_FILE_DIRECTIVE,
    C_FILE_DIRECTIVES,
    C_RODATA_DIRECTIVE,
    LABEL_DIRECTIVES,
    RODATA_SUFFIX,
    read_rows,
)

REPORT_VERSION = 2
AREAS = {"us": US_AREAS, "jp": JP_AREAS}
CATEGORIES = [("game", "Game"), ("libc", "libc"), ("krawall", "Krawall")]
MEASURE_FIELDS = [
    "total_code", "matched_code", "total_data", "matched_data",
    "complete_code", "complete_data", "total_units", "complete_units",
]


def read_units(path: str) -> list[dict]:
    """Returns one entry per region row: start, end, name, matched, source."""
    rows = []
    c_sources = {}
    for lineno, parts in read_rows(path):
        directive = parts[0]
        if directive in LABEL_DIRECTIVES:
            continue
        try:
            start, end = int(parts[1], 16), int(parts[2], 16)
        except (IndexError, ValueError):
            sys.exit(f"{path}:{lineno}: cannot parse region row")
        name = parts[-1]
        source = None
        if directive in C_FILE_DIRECTIVES:
            source = parts[3]
            c_sources[name] = source
        elif directive == ASM_FILE_DIRECTIVE:
            source = parts[3]
        rows.append({
            "start": start, "end": end, "directive": directive,
            "name": name, "source": source,
        })
    for row in rows:
        if row["directive"] == C_RODATA_DIRECTIVE:
            row["source"] = c_sources.get(row["name"])
            row["name"] += RODATA_SUFFIX
    rows.sort(key=lambda r: r["start"])
    for a, b in zip(rows, rows[1:]):
        if b["start"] < a["end"]:
            sys.exit(f"{path}: overlapping regions {a['name']} and {b['name']}")
    return rows


def is_matched(directive: str | None, is_code: bool) -> bool:
    if directive is None:
        return False
    if directive in C_FILE_DIRECTIVES or directive == C_RODATA_DIRECTIVE:
        return True
    # asm-file rows and extracted asset directives.
    return not is_code


def category_of(area: str, source: str | None) -> str:
    if "krawall" in area:
        return "krawall"
    if source and source.startswith("src/libc/"):
        return "libc"
    return "game"


def empty_measures() -> dict:
    return {f: 0 for f in MEASURE_FIELDS}


def finish(m: dict) -> dict:
    """Adds the percentage fields the way objdiff computes them."""
    def pct(n, d):
        return 100.0 if d == 0 else 100.0 * n / d
    out = dict(m)
    out["fuzzy_match_percent"] = pct(m["matched_code"], m["total_code"])
    out["matched_code_percent"] = pct(m["matched_code"], m["total_code"])
    out["matched_data_percent"] = pct(m["matched_data"], m["total_data"])
    out["complete_code_percent"] = pct(m["complete_code"], m["total_code"])
    out["complete_data_percent"] = pct(m["complete_data"], m["total_data"])
    out["total_functions"] = 0
    out["matched_functions"] = 0
    out["matched_functions_percent"] = 0.0
    return out


def add(dst: dict, src: dict) -> None:
    for f in MEASURE_FIELDS:
        dst[f] += src[f]


def build_report(ver: str) -> dict:
    rows = read_units(f"regions.{ver}.txt")
    units = []
    seen = {}
    for area, lo, hi in AREAS[ver]:
        is_code = area.startswith("code")
        pieces = []
        cur = lo
        for row in rows:
            s, e = max(row["start"], lo), min(row["end"], hi)
            if e <= s:
                continue
            if s > cur:
                pieces.append((cur, s, None))
            pieces.append((s, e, row))
            cur = max(cur, e)
        if cur < hi:
            pieces.append((cur, hi, None))

        for s, e, row in pieces:
            size = e - s
            if row is None:
                name, directive, source = f"raw_{s:08X}", None, None
            else:
                name, directive, source = row["name"], row["directive"], row["source"]
            # A row split at an area boundary appears once per area.
            if name in seen:
                seen[name] += 1
                name = f"{name}.{seen[name]}"
            else:
                seen[name] = 0
            matched = is_matched(directive, is_code)
            m = empty_measures()
            m["total_units"] = 1
            m["complete_units"] = int(matched)
            kind = "code" if is_code else "data"
            m[f"total_{kind}"] = size
            if matched:
                m[f"matched_{kind}"] = size
                m[f"complete_{kind}"] = size
            metadata = {
                "complete": matched,
                "progress_categories": [category_of(area, source)],
                "auto_generated": row is None,
            }
            if source:
                metadata["source_path"] = source
            units.append({
                "name": name,
                "measures": m,
                "metadata": metadata,
                "sections": [{
                    "name": ".text" if is_code else ".data",
                    "size": size,
                    "fuzzy_match_percent": 100.0 if matched else 0.0,
                    "metadata": {"virtual_address": s},
                }],
            })

    total = empty_measures()
    by_cat = {cid: empty_measures() for cid, _ in CATEGORIES}
    for unit in units:
        add(total, unit["measures"])
        for cid in unit["metadata"]["progress_categories"]:
            add(by_cat[cid], unit["measures"])
    for unit in units:
        unit["measures"] = finish(unit["measures"])

    return {
        "version": REPORT_VERSION,
        "measures": finish(total),
        "units": units,
        "categories": [
            {"id": cid, "name": cname, "measures": finish(by_cat[cid])}
            for cid, cname in CATEGORIES
        ],
    }


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("ver", choices=sorted(AREAS))
    ap.add_argument("-o", "--output", help="default: build/<ver>/report.json")
    args = ap.parse_args()

    out = args.output or f"build/{args.ver}/report.json"
    os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
    with open(out, "w") as f:
        json.dump(build_report(args.ver), f, indent=1)
        f.write("\n")


if __name__ == "__main__":
    main()
