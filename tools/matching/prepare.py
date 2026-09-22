"""Prepare an isolated candidate without editing the production manifest."""
import json
import re
import shutil
from pathlib import Path
from .workspace import ROOT
from .reference import build_target_asm, ram_symbols
from .compile import run


def link_binary(obj, out, start, baseline):
    """Resolve against baseline symbols, preserving ARM/Thumb symbol types."""
    obj, out, baseline = Path(obj).resolve(), Path(out).resolve(), Path(baseline).resolve()
    script = out.with_suffix('.ld')
    symbols = baseline.with_suffix('.symbols.ld')
    prefix = symbols.read_text() if symbols.exists() else ''
    script.write_text(prefix + f'SECTIONS {{ . = 0x{start:x}; .text : {{ *(.text) }} }}\n')
    elf = out.with_suffix('.elf')
    run(['arm-none-eabi-ld', '--just-symbols=' + str(baseline), '-T', script,
         '-o', elf, obj])
    run(['arm-none-eabi-objcopy', '-O', 'binary', '--only-section=.text', elf, out])
    return out.read_bytes()


def prepare(ver, name, source=None, end=None, profile_source=None, reference_name=None):
    if not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', name):
        raise ValueError('expected a C function name')
    rows = [line.split('#', 1)[0].split() for line in (ROOT / f'regions.{ver}.txt').read_text().splitlines()]
    row = next((r for r in rows if len(r) == 5 and r[0] in {'c-file', 'c-file-O1'} and r[4] == name), None)
    if not source and row:
        source = row[3]
    if not source:
        raise ValueError('unmatched functions need --source pointing to a draft C file')
    reference_name = reference_name or name
    dump = (ROOT / f'build/{ver}/full_disasm.s').read_text()
    match = re.search(r'^\s*(thumb|arm)_func_start\s+' + re.escape(reference_name)
                      + r'\s*\n' + re.escape(reference_name) + r':\s*@\s*(0x[\da-fA-F]+)', dump, re.M)
    if not match:
        raise ValueError('function needs an address-annotated entry in full_disasm.s; refresh disassembly or check --reference-name')
    mode, addr = match.groups()
    if mode != 'thumb':
        raise ValueError('candidate compiler profiles currently support Thumb C only; ARM needs an identified profile')
    start = int(addr, 16)
    if row and start != int(row[1], 0):
        raise ValueError(f'reference {reference_name} starts at {start:#x}, but manifest {name} starts at {int(row[1], 0):#x}; investigate names and use --reference-name only for a verified alias')
    if end is None and row:
        end = int(row[2], 0)
    if end is None or end <= start:
        raise ValueError('unmatched functions need --end 0xADDRESS after tracing every path and literal pool')
    baseline = ROOT / f'build/{ver}/rom.elf'
    if not baseline.exists():
        raise ValueError(f'run just compare {ver} first to provide baseline symbols')
    path = ROOT / 'build/matching' / ver / name
    path.mkdir(parents=True, exist_ok=False)
    ref = path / 'reference'
    ref.mkdir()
    shutil.copy2(baseline, ref / 'baseline.elf')
    (ref / 'baseline.symbols.ld').write_text(''.join(
        f'{symbol} = 0x{address:x};\n' for address, symbol in ram_symbols(ver).items()))
    baseline = ref / 'baseline.elf'
    asm, _ = build_target_asm(ver, reference_name, end)
    if reference_name != name:
        asm = re.sub(r'\b' + re.escape(reference_name) + r'\b', name, asm)
    (ref / 'target.s').write_text(asm)
    run(['arm-none-eabi-as', '-mcpu=arm7tdmi', '-o', ref / 'target.o', ref / 'target.s'])
    # Resolve generated address labels absent from the production symbol table.
    undefined = run(['arm-none-eabi-nm', '-u', ref / 'target.o'], capture_output=True, text=True).stdout
    labels = ''.join(f'.global {n}\n.set {n}, 0x{n[1:]}\n' for n in re.findall(r'\b_[0-9A-Fa-f]{8}\b', undefined))
    if labels:
        (ref / 'target.s').write_text(asm + labels)
        run(['arm-none-eabi-as', '-mcpu=arm7tdmi', '-o', ref / 'target.o', ref / 'target.s'])
    got = link_binary(ref / 'target.o', ref / 'linked.bin', start, baseline)
    want = (ROOT / f'baserom.{ver}.gba').read_bytes()[start - 0x08000000:end - 0x08000000]
    (ref / 'rom.bin').write_bytes(want)
    if len(want) != end - start or got != want:
        raise ValueError(f'extracted reference does not reproduce requested extent ({len(got)} vs {end-start} bytes); inspect {ref}. Next-label extraction may include extra data or omit shared pools. Workspace retained for diagnosis.')
    current = path / 'current'
    current.mkdir()
    shutil.copy2(source, current / 'candidate.c')
    profile_source = profile_source or (row[3] if row else str(source))
    try:
        profile_source = str(Path(profile_source).resolve().relative_to(ROOT))
    except ValueError:
        pass
    meta = dict(version=ver, name=name, start=start, end=end, mode=mode,
                profile_source=profile_source, reference_name=reference_name, source=str(Path(source).resolve()),
                o1=bool(row and row[0] == 'c-file-O1'),
                boundary='manifest' if row else 'user-specified',
                reference_verified=True)
    (path / 'workspace.json').write_text(json.dumps(meta, indent=2) + '\n')
    print(f'{path}\nReference bytes verified. Extent provenance: {meta["boundary"]}; reachability still requires human/agent analysis.')
