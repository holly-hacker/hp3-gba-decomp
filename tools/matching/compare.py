"""Selected-function operand diagnostics plus exact linked-region verification."""
import difflib
import hashlib
import json
import re
from .compile import run
from .prepare import link_binary
from .workspace import load


def instructions(obj, name):
    text = run(['arm-none-eabi-objdump', '-dr', '--disassemble=' + name, obj],
               capture_output=True, text=True).stdout
    result = []
    for line in text.splitlines():
        m = re.match(r'^\s*([0-9a-f]+):\s+(?:[0-9a-f]{2,8}\s+)+\s*([a-z][\w.]*)\s*(.*)', line)
        if m:
            mnemonic = m[2].removesuffix('.n')
            mnemonic = {'bhs': 'bcs', 'blo': 'bcc'}.get(mnemonic, mnemonic)
            operand = re.sub(r'\s*;.*', '', m[3]).strip()
            result.append((mnemonic, operand))
        elif re.search(r'R_ARM_\w+', line):
            result.append(('relocation', line.strip().split(':', 1)[-1].strip()))
    return result


def category(a, b):
    if a[0] == 'relocation' or b[0] == 'relocation':
        return 'relocation'
    if a[0] != b[0]:
        return 'instruction'
    scrub = lambda s: re.sub(r'\b(?:r\d+|sp|lr|pc|ip|fp|sl|sb)\b', 'REG', s)
    if a[1] != b[1] and scrub(a[1]) == scrub(b[1]):
        return 'register'
    if a[0].startswith('b'):
        return 'branch/operand'
    return 'operand/constant/address'


def compare(path):
    path, meta = load(path)
    obj = path / 'current/candidate.o'
    stamp = json.loads((path / 'current/compiled.json').read_text())
    for file, key in [(path / 'current/candidate.c', 'source_sha256'), (obj, 'object_sha256')]:
        if hashlib.sha256(file.read_bytes()).hexdigest() != stamp[key]:
            raise ValueError('candidate source/object changed since compilation; run compile again')
    want = (path / 'reference/rom.bin').read_bytes()
    got = link_binary(obj, path / 'current/linked.bin', meta['start'], path / 'reference/baseline.elf')
    differences = sum(a != b for a, b in zip(want, got)) + abs(len(want) - len(got))
    print(f'Linked region: expected {len(want)} bytes, candidate {len(got)} bytes; {differences} differing byte positions')
    if want == got:
        print('EXACT REGION MATCH (finish with a fresh production build and both-version verification)')
        return 0
    a = instructions(path / 'reference/target.o', meta['name'])
    b = instructions(obj, meta['name'])
    if not a or not b:
        raise ValueError('selected function has no decoded instructions; inspect symbols/mode')
    groups = 0
    for tag, i, j, k, l in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == 'equal':
            continue
        groups += 1
        print(f'{tag} reference[{i}:{j}] candidate[{k}:{l}]')
        for n in range(max(j-i, l-k)):
            left = a[i+n] if i+n < j else ('', '')
            right = b[k+n] if k+n < l else ('', '')
            print(f'  {category(left, right):24} {" ".join(left):55} | {" ".join(right)}')
    print(f'{groups} operand-aware groups; diagnostic categories are hints, not proof of cause.')
    print('Raw bytes include literal pools and padding; object operands can differ due to relocation/layout.')
    return 1
