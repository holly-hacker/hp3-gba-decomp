"""Staleness check for pack steps: is an output newer than all its inputs?"""
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# Codecs shared by the pack steps; editing one repacks everything.
CODECS = [ROOT / "tools" / d for d in ("graphics", "images", "room_graphics")]


def fresh(output: Path, *inputs: Path) -> bool:
    if not output.is_file():
        return False
    newest = max((f.stat().st_mtime for p in [*inputs, *CODECS]
                  for f in (p.rglob("*") if p.is_dir() else [p]) if f.is_file()),
                 default=0)
    return output.stat().st_mtime > newest
