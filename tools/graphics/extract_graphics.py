#!/usr/bin/env python3
"""Extract graphics runs from the baseroms into data/graphics/.

Each run is extracted once, from the first version whose manifest has it
(us, then jp), and must rebuild to that ROM's bytes. With no run names,
data/graphics/ is cleared first and every run is extracted; with names, only
those runs' files and settings are replaced. Each feature's graphics.json
lists its runs in ROM order. See tools/graphics/runs.py.

data/graphics/ is gitignored, same footing as the baserom (AGENTS.md hard
rule 2); extraction overwrites local edits.

Usage: extract_graphics.py [run ...]
"""
import json
import shutil
import sys
from pathlib import Path

import runs

VERSIONS = ("us", "jp")


def remove(path: Path) -> None:
    if path.is_dir():
        shutil.rmtree(path)
    elif path.exists():
        path.unlink()


def main() -> None:
    wanted = sys.argv[1:]
    try:
        plan: dict[str, tuple[str, runs.Row]] = {}
        for ver in VERSIONS:
            for row in runs.rows(ver):
                if not wanted or row.name in wanted:
                    plan.setdefault(row.name, (ver, row))
        missing = set(wanted) - set(plan)
        if missing:
            raise ValueError(f"no manifest has a graphics run named {', '.join(sorted(missing))}")
        if not wanted:
            remove(runs.DATA)

        by_feature: dict[Path, list[tuple[str, runs.Row]]] = {}
        for ver, row in plan.values():
            by_feature.setdefault(row.feature, []).append((ver, row))
        roms = {ver: (runs.ROOT / f"baserom.{ver}.gba").read_bytes() for ver in VERSIONS}
        for feature, planned in sorted(by_feature.items()):
            index = feature / runs.INDEX
            settings = json.loads(index.read_text())["runs"] if index.is_file() else {}
            for ver, row in planned:
                kind = runs.KINDS[row.kind]
                if row.name in settings:
                    for file in kind.files(settings[row.name]):
                        remove(feature / file)
                feature.mkdir(parents=True, exist_ok=True)
                try:
                    settings[row.name] = kind.extract(roms[ver], ver, row.start, row.end, row.name, feature)
                except (ValueError, IndexError) as exc:
                    raise ValueError(f"{ver}: {row.name}: {exc}") from None
                print(f"{ver}: extracted {row.name} into {feature.relative_to(runs.ROOT)}")
            runs.write_index(feature, settings)
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
