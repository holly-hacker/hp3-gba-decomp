"""Content-addressed cache for the pack, compile and assemble steps.

A result is stored under build/cache/<namespace>/ by a SHA-256 key over
everything that determines it: its input bytes, its settings, and the
source of the tools/ modules that compute it. Keys never depend on
timestamps or on the manifest as a whole, so editing regions.<ver>.txt only
recomputes what the edit actually changed, and results are shared between
versions.

Callers always write a result to its usual build/<ver>/ path. The
assembler, the generated linker script and the ELF only see those paths;
the cache directory and its keys never appear in them. Deleting
build/cache/ is always safe.
"""
import hashlib
import json
import os
import pickle
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CACHE = ROOT / "build" / "cache"

_file_digests: dict[str, str] = {}


def file_digest(path) -> str:
    """SHA-256 of a file's contents, computed once per process."""
    key = os.path.abspath(path)
    if key not in _file_digests:
        with open(key, "rb") as f:
            _file_digests[key] = hashlib.file_digest(f, "sha256").hexdigest()
    return _file_digests[key]


def tree_digest(directory: Path) -> list[tuple[str, str]]:
    """(relative path, digest) of every file under a directory."""
    return [(p.relative_to(directory).as_posix(), file_digest(p))
            for p in sorted(directory.rglob("*")) if p.is_file()]


def digest(*parts) -> str:
    """A key over bytes and JSON-like values."""
    h = hashlib.sha256()
    for part in parts:
        data = part if isinstance(part, bytes) else json.dumps(
            part, sort_keys=True, default=str).encode()
        h.update(len(data).to_bytes(8, "little"))
        h.update(data)
    return h.hexdigest()


def tool_digest() -> str:
    """Digest of the Python interpreter and of every tools/ module loaded so
    far: the code that computes the caller's results. Call it after the
    caller's imports."""
    tools = ROOT / "tools"
    files = sorted({Path(m.__file__).resolve() for m in list(sys.modules.values())
                    if getattr(m, "__file__", None)
                    and Path(m.__file__).resolve().is_relative_to(tools)})
    return digest(os.path.realpath(sys.executable),
                  [(f.relative_to(ROOT).as_posix(), file_digest(f)) for f in files])


def _path(namespace: str, key: str) -> Path:
    return CACHE / namespace / key[:2] / key


def load(namespace: str, key: str) -> bytes | None:
    try:
        return _path(namespace, key).read_bytes()
    except FileNotFoundError:
        return None


def store(namespace: str, key: str, data: bytes) -> None:
    path = _path(namespace, key)
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=path.parent)
    with os.fdopen(fd, "wb") as f:
        f.write(data)
    os.replace(tmp, path)


def write_if_changed(path, data: bytes | str) -> None:
    """Write a file unless it already holds exactly this content."""
    path = Path(path)
    if isinstance(data, str):
        data = data.encode()
    try:
        if path.read_bytes() == data:
            return
    except FileNotFoundError:
        path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)


def _call(fn, args):
    return fn(*args)


def cached_map(namespace: str, fn, items: list[tuple], keys: list[str]) -> list:
    """[fn(*item) for item in items], taking each result from the cache by
    the matching key and computing the misses across processes. fn must be
    a module-level function and its results picklable; exceptions propagate
    and are not cached."""
    results, misses = [None] * len(items), []
    for i, key in enumerate(keys):
        data = load(namespace, key)
        if data is None:
            misses.append(i)
        else:
            results[i] = pickle.loads(data)
    if len(misses) > 1:
        with ProcessPoolExecutor() as pool:
            computed = list(pool.map(_call, [fn] * len(misses), [items[i] for i in misses]))
    else:
        computed = [fn(*items[i]) for i in misses]
    for i, value in zip(misses, computed):
        store(namespace, keys[i], pickle.dumps(value))
        results[i] = value
    return results
