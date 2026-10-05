"""Graphics runs: the manifest rows that pack_graphics.py builds.

A row `<kind> <start> <end> <dir> <Name>` claims one run of contiguous
graphics of one kind (the directive, a key of KINDS). <dir> is a feature
directory under data/graphics/ (data/graphics/minigames/pumpkin), shared by
every run of that feature; its graphics.json maps each run's name to its
settings, and the files those settings name sit beside it. Each feature has
one generated header, include/gen/graphics/<feature path>.h, declaring the
labels of all its runs in every version. See docs/formats/graphics.md
("Graphics build format").

Each kind is a module in kinds/ with:
  ITEMS                   the settings key listing the run's items (None: the
                          run is one item)
  check(run)              raise ValueError for invalid settings
  files(run)              the feature directory entries the run owns
  item_files(run, item)   the files one item is built from
  build(source, name, settings, item) -> [(label, bytes)], where settings
                          is the run without its items
  extract(rom, ver, start, end, name, source) -> settings; writes the files
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
for sub in ("tools", "tools/graphics", "tools/images", "tools/graphic_blob", "tools/fonts",
            "tools/room_graphics"):
    if str(ROOT / sub) not in sys.path:
        sys.path.insert(0, str(ROOT / sub))

from kinds import fonts, graphic_blobs, image_bank, room_graphics, tile_frames, tile_streams  # noqa: E402

KINDS = {"image-bank": image_bank, "graphic-blobs": graphic_blobs, "tile-streams": tile_streams,
         "tile-frames": tile_frames, "fonts": fonts, "room-graphics": room_graphics}
DATA = ROOT / "data" / "graphics"
INDEX = "graphics.json"


class Row:
    def __init__(self, kind: str, start: int, end: int, feature: Path, name: str):
        self.kind, self.start, self.end, self.feature, self.name = kind, start, end, feature, name


def rows(ver: str) -> list[Row]:
    """The graphics rows of regions.<ver>.txt, in address order."""
    path = ROOT / f"regions.{ver}.txt"
    out = []
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        parts = raw.split("#", 1)[0].split()
        if not parts or parts[0] not in KINDS:
            continue
        if len(parts) != 5:
            raise ValueError(f"{path}:{lineno}: expected {parts[0]} <start> <end> <dir> <name>")
        kind, start, end, feature, name = parts
        if not (ROOT / feature).resolve().is_relative_to(DATA):
            raise ValueError(f"{path}:{lineno}: {feature} is not under data/graphics/")
        out.append(Row(kind, int(start, 16), int(end, 16), ROOT / feature, name))
    return sorted(out, key=lambda r: r.start)


def all_rows() -> dict[str, Row]:
    """Every run named by any version's manifest, by name. A run must have
    the same kind and feature directory in every manifest."""
    found: dict[str, Row] = {}
    for path in sorted(ROOT.glob("regions.*.txt")):
        for row in rows(path.name.split(".")[1]):
            seen = found.setdefault(row.name, row)
            if (seen.kind, seen.feature) != (row.kind, row.feature):
                raise ValueError(f"{path.name}: {row.name} is {row.kind} in {row.feature}, "
                                 f"elsewhere {seen.kind} in {seen.feature}")
    return found


def items(kind: str, run: dict) -> list:
    key = KINDS[kind].ITEMS
    return [run] if key is None else run[key]


def load(feature: Path, kinds: dict[str, str]) -> dict[str, dict]:
    """A feature's runs, checked. kinds maps each run name to its kind."""
    path = feature / INDEX
    index = json.loads(path.read_text())
    if set(index) != {"format", "runs"} or index["format"] != 1:
        raise ValueError(f"{path}: expected format 1 with runs")
    owned: dict[str, str] = {INDEX: ""}
    for name, run in index["runs"].items():
        if name not in kinds:
            raise ValueError(f"{path}: no manifest row names run {name}")
        try:
            KINDS[kinds[name]].check(run)
        except (ValueError, TypeError, KeyError) as exc:
            raise ValueError(f"{path}: {name}: {exc}") from None
        for file in KINDS[kinds[name]].files(run):
            if file in owned:
                raise ValueError(f"{path}: {name} and {owned[file] or INDEX} both use {file}")
            owned[file] = name
    # A subdirectory with its own index is a nested feature, such as the
    # runs of a feature that only one version has.
    unowned = sorted({p.name for p in feature.iterdir() if not (p / INDEX).is_file()} - set(owned))
    if unowned:
        raise ValueError(f"{path}: files no run uses: {', '.join(unowned)}")
    return index["runs"]


def header_path(feature: Path) -> Path:
    return ROOT / "include" / "gen" / "graphics" / feature.relative_to(DATA).with_suffix(".h")


def _dump(value, indent: str = "") -> str:
    """JSON with short containers on one line and long ones split per element."""
    flat = json.dumps(value)
    if len(indent) + len(flat) <= 100 or not isinstance(value, (dict, list)) or not value:
        return flat
    inner = indent + "  "
    if isinstance(value, dict):
        body = [f"{inner}{json.dumps(k)}: {_dump(v, inner)}" for k, v in value.items()]
        return "{\n" + ",\n".join(body) + f"\n{indent}}}"
    return "[\n" + ",\n".join(inner + _dump(v, inner) for v in value) + f"\n{indent}]"


def write_index(feature: Path, runs: dict[str, dict]) -> None:
    feature.mkdir(parents=True, exist_ok=True)
    (feature / INDEX).write_text(_dump({"format": 1, "runs": runs}) + "\n")
