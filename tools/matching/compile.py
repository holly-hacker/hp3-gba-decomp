"""Compile using the production profile and section handling."""
import subprocess
import hashlib
import json
from pathlib import Path
from tools.c.compile_c import agbcc_prefix, profile, place_in_text
from .workspace import ROOT, load


def run(args, **kwargs):
    return subprocess.run([str(x) for x in args], check=True, **kwargs)


def compile_source(source, output, profile_source, dumps=None, preprocessed=False, quote_dir=None):
    source, output = Path(source).resolve(), Path(output).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.unlink(missing_ok=True)  # A failed compile must not leave a stale candidate object.
    cc, cppflags, flags = profile(profile_source, agbcc_prefix())
    pre = source.read_text() if preprocessed else run(
        ['cpp', *cppflags, '-iquote', str(quote_dir or source.parent), source],
        cwd=ROOT, capture_output=True, text=True).stdout
    inp = output.with_suffix('.i')
    inp.write_text(pre)
    asm = output.with_suffix('.s')
    if dumps:
        flags = [*flags, '-d' + dumps]
    run([cc, *flags, '-o', asm, inp], cwd=output.parent)
    asm.write_text('.syntax divided\n' + place_in_text(asm.read_text(), profile_source)
                   + '\n\t.align 2, 0\n.syntax unified\n')
    run(['arm-none-eabi-as', '-mcpu=arm7tdmi', '-o', output, asm])
    return output


def compile_workspace(path, source=None, dumps=None):
    path, meta = load(path)
    current = path / 'current'
    current.mkdir(exist_ok=True)
    if source:
        import shutil
        shutil.copy2(source, current / 'candidate.c')
    output = compile_source(current / 'candidate.c', current / 'candidate.o',
                            meta['profile_source'], dumps, quote_dir=Path(meta['source']).parent)
    (current / 'compiled.json').write_text(json.dumps({
        'source_sha256': hashlib.sha256((current / 'candidate.c').read_bytes()).hexdigest(),
        'object_sha256': hashlib.sha256(output.read_bytes()).hexdigest(),
    }) + '\n')
    print(output)
