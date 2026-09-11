"""Workspace metadata and immutable candidate snapshots."""
import json
import re
import shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def load(path):
    path = Path(path).resolve()
    return path, json.loads((path / 'workspace.json').read_text())


def snapshot(path, name):
    path, meta = load(path)
    if not re.fullmatch(r'[A-Za-z0-9_-]+', name):
        raise ValueError('snapshot name must contain letters, digits, underscores or hyphens')
    dest = path / 'candidates' / name
    dest.mkdir(parents=True, exist_ok=False)
    shutil.copytree(path / 'current', dest / 'current')
    shutil.copy2(path / 'workspace.json', dest / 'workspace.json')
    print(dest)
