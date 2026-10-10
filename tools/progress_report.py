#!/usr/bin/env python3
"""Write an objdiff-format progress report for decomp.dev from regions.<ver>.txt.

The report follows objdiff's report.proto (version 2), as JSON. It is
derived from the manifest alone, without building: every c-file row is
byte-exact because the build compares against the baserom.

Areas and code blocks come from tools/rom_layout.json. Each code block is
one unit, and its functions are the manifest's function rows and region
starts plus the seeds in functions.<ver>.cfg. A function runs to the next
function start or region boundary; it is matched when it lies in compiled C
(c-file, c-file-O1) or committed assembly (asm-file), which in the code
areas is ARM code, the ROM header or library assembly. Code bytes are
matched, and complete (linked from source), on the same terms; a block is a
complete unit when all of it is.

In the data areas, units are the manifest's region rows plus one
auto-generated unit per unclaimed gap. A data unit counts as matched (and
complete) when it is compiled C (c-file, c-file-O1, c-rodata), an asm-file
row or an extracted asset directive.

Progress categories: a code block's own category (`krawall`, `libc` or
`game`); for data, `krawall` in the Krawall data area and `game` elsewhere.
"""
import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import rom_layout  # noqa: E402
from manifest import (  # noqa: E402
    ASM_FILE_DIRECTIVE,
    C_FILE_DIRECTIVES,
    C_RODATA_DIRECTIVE,
    LABEL_DIRECTIVES,
    RODATA_SUFFIX,
    read_rows,
)

REPORT_VERSION = 2
VERSIONS = ["us", "jp"]
CATEGORIES = [("game", "Game"), ("libc", "libc"), ("krawall", "Krawall")]
MEASURE_FIELDS = [
    "total_code", "matched_code", "total_data", "matched_data",
    "complete_code", "complete_data", "total_units", "complete_units",
    "total_functions", "matched_functions",
]
FUNCTION_DIRECTIVES = {"thumb-func", "arm-func"}
MATCHED_CODE_DIRECTIVES = C_FILE_DIRECTIVES | {ASM_FILE_DIRECTIVE}
CFG_DIRECTIVES = {"thumb_func", "arm_func"}


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


def read_function_starts(ver: str, rows: list[dict]) -> dict[int, str]:
    """Returns address -> name for every known function start.

    Names prefer the manifest's function rows, then functions.<ver>.cfg,
    then the name of the region row starting there.
    """
    names: dict[int, str] = {}
    for row in rows:
        if row["directive"] in C_FILE_DIRECTIVES or row["directive"] == ASM_FILE_DIRECTIVE:
            names[row["start"]] = row["name"]
    with open(f"functions.{ver}.cfg") as f:
        for line in f:
            parts = line.split("#", 1)[0].split()
            if len(parts) >= 2 and parts[0] in CFG_DIRECTIVES:
                address = int(parts[1], 16)
                if len(parts) >= 3:
                    names[address] = parts[2]
                else:
                    names.setdefault(address, f"sub_{address:08X}")
    for _, parts in read_rows(f"regions.{ver}.txt"):
        if parts[0] in FUNCTION_DIRECTIVES:
            names[int(parts[1], 16)] = parts[2]
    return names


def read_functions(ver: str, rows: list[dict], blocks: list) -> list[dict]:
    """Returns the functions in the code blocks: start, size, name, matched.

    A function ends at the next function start, the end of the region row
    holding it (or the start of the next one) and the end of its block.
    """
    names = read_function_starts(ver, rows)
    bounds = sorted({r["start"] for r in rows} | {r["end"] for r in rows})
    starts = sorted(names)
    functions = []
    for block in blocks:
        inside = [a for a in starts if block.start <= a < block.end]
        for a, next_start in zip(inside, inside[1:] + [block.end]):
            end = min([next_start] + [b for b in bounds if b > a])
            row = next((r for r in rows if r["start"] <= a < r["end"]), None)
            functions.append({
                "start": a, "size": end - a, "name": names[a],
                "matched": row is not None and row["directive"] in MATCHED_CODE_DIRECTIVES,
            })
    return functions


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
    out["matched_functions_percent"] = pct(m["matched_functions"], m["total_functions"])
    return out


def add(dst: dict, src: dict) -> None:
    for f in MEASURE_FIELDS:
        dst[f] += src[f]


def unique_name(name: str, seen: dict[str, int]) -> str:
    if name in seen:
        seen[name] += 1
        return f"{name}.{seen[name]}"
    seen[name] = 0
    return name


def matched_bytes(rows: list[dict], lo: int, hi: int) -> int:
    return sum(max(0, min(r["end"], hi) - max(r["start"], lo))
               for r in rows if r["directive"] in MATCHED_CODE_DIRECTIVES)


def block_unit(block, rows: list[dict], functions: list[dict], seen: dict[str, int]) -> dict:
    size = block.end - block.start
    matched = matched_bytes(rows, block.start, block.end)
    complete = matched == size
    m = empty_measures()
    m["total_units"] = 1
    m["complete_units"] = int(complete)
    m["total_code"] = size
    m["matched_code"] = matched
    m["complete_code"] = matched
    m["total_functions"] = len(functions)
    m["matched_functions"] = sum(f["matched"] for f in functions)
    return {
        "name": unique_name(block.name, seen),
        "measures": m,
        "metadata": {
            "complete": complete,
            "progress_categories": [block.category],
            "auto_generated": False,
        },
        "sections": [{
            "name": ".text",
            "size": size,
            "fuzzy_match_percent": 100.0 * matched / size,
            "metadata": {"virtual_address": block.start},
        }],
        "functions": [{
            "name": f["name"],
            "size": f["size"],
            "fuzzy_match_percent": 100.0 if f["matched"] else 0.0,
            "metadata": {"virtual_address": f["start"]},
        } for f in functions],
    }


def build_report(ver: str) -> dict:
    rows = read_units(f"regions.{ver}.txt")
    areas, blocks = rom_layout.load(ver)
    functions = read_functions(ver, rows, blocks)
    units = []
    seen = {}
    for block in blocks:
        inside = [f for f in functions if block.start <= f["start"] < block.end]
        units.append(block_unit(block, rows, inside, seen))
    for area in areas:
        if area.is_code:
            continue
        lo, hi = area.start, area.end
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
            name = unique_name(name, seen)
            matched = directive is not None
            m = empty_measures()
            m["total_units"] = 1
            m["complete_units"] = int(matched)
            m["total_data"] = size
            if matched:
                m["matched_data"] = size
                m["complete_data"] = size
            metadata = {
                "complete": matched,
                "progress_categories": [category_of(area.name, source)],
                "auto_generated": row is None,
            }
            if source:
                metadata["source_path"] = source
            units.append({
                "name": name,
                "measures": m,
                "metadata": metadata,
                "sections": [{
                    "name": ".data",
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
    ap.add_argument("ver", choices=VERSIONS)
    ap.add_argument("-o", "--output", help="default: build/<ver>/report.json")
    args = ap.parse_args()

    out = args.output or f"build/{args.ver}/report.json"
    os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
    with open(out, "w") as f:
        json.dump(build_report(args.ver), f, indent=1)
        f.write("\n")


if __name__ == "__main__":
    main()
