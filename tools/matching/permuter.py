"""Generate a production-profile permuter project and stop the whole process group on timeout."""
import os
import shlex
import shutil
import signal
import subprocess
from pathlib import Path
from .compile import run
from .workspace import ROOT, load
from tools.c.compile_c import agbcc_prefix, profile


def setup(path):
    path, meta = load(path)
    dest = path / 'permuter'
    dest.mkdir(exist_ok=False)
    shutil.copy2(path / 'reference/target.o', dest / 'target.o')
    source = path / 'current/candidate.c'
    _, flags, _ = profile(meta['profile_source'], agbcc_prefix())
    pre = run(['cpp', *flags, '-iquote', str(Path(meta['source']).parent), source], cwd=ROOT, capture_output=True, text=True).stdout
    (dest / 'base.c').write_text(pre)
    command = ['python3', '-m', 'tools.matching', 'compile-object',
               '--profile-source', meta['profile_source'], '--preprocessed']
    (dest / 'compile.sh').write_text('#!/bin/sh\nset -eu\n'
        + 'input=$(realpath "$1")\nshift\n[ "$1" = "-o" ]\nshift\noutput=$(realpath -m "$1")\n'
        + 'cd ' + shlex.quote(str(ROOT)) + '\nexec ' + shlex.join(command) + ' "$input" -o "$output"\n')
    (dest / 'compile.sh').chmod(0o755)
    (dest / 'settings.toml').write_text(f'func_name = "{meta["name"]}"\ncompiler_type = "gcc"\n')
    print(dest)


def bounded_run(command, seconds, log):
    with open(log, 'w') as stream:
        proc = subprocess.Popen(command, stdout=stream, stderr=subprocess.STDOUT, start_new_session=True)
        try:
            return proc.wait(timeout=seconds)
        except (subprocess.TimeoutExpired, KeyboardInterrupt):
            try:
                os.killpg(proc.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass
            try:
                proc.wait(timeout=3)
            except subprocess.TimeoutExpired:
                pass
            # Workers can outlive their parent; terminate the entire remaining group.
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait()
            return 124


def search(path, seconds=120, jobs=2, approved_long_run=False):
    if seconds <= 0 or jobs <= 0:
        raise ValueError('seconds and jobs must be positive')
    if seconds > 180 and not approved_long_run:
        raise ValueError('runs over 180 seconds require user approval, then --approved-long-run')
    path, _ = load(path)
    dest = path / 'permuter'
    if not (dest / 'settings.toml').exists():
        raise ValueError('run permuter-setup first')
    log = dest / 'run.log'
    code = bounded_run(['permuter.py', str(dest), '-j', str(jobs), '--stop-on-zero', '--best-only'], seconds, log)
    print(f'Exit {code}; results retained in {dest}; log: {log}. Review semantics and UB before adopting.')
    return code
