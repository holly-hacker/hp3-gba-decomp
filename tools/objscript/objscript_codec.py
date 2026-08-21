"""Shared format knowledge for the object/spell behavior-script bytecode
interpreter (`InterpretObjectScript`, US `0x08018CC0`). See
docs/formats/object_script.md for how each constant below was identified.

Byte format: a script is a flat sequence of instructions, each an opcode
byte followed by `opcode_operand_length(opcode)` operand bytes. No length
prefix or end-of-script marker beyond opcode `0` (`End`) terminating
control flow -- a script's total byte length is fixed externally, by the
gap between its `g_apEffectScripts` pointer and the next one (or the
table itself, for the last script).

Opcode metadata (name, operand length, and -- for opcode 0x97,
StatusEffect, which reads its own first operand byte as a second-level
case selector -- named sub-cases) lives in opcodes.json next to this
file, not here. It's interpreter/ISA knowledge (like a CPU's mnemonic
table), not extracted game content or ROM addresses, so unlike
data/scripts/ it's committed rather than gitignored, and unlike
docs/formats/object_script.md's prose it deliberately carries NO
addresses -- see that doc's "Why no addresses in opcodes.json" for why
(shiftable-build/moddability and US-vs-JP offset differences both break
if opcode metadata pins a ROM address). Naming a new opcode means
editing opcodes.json's "name" (or a StatusEffect sub-case's entry under
"sub_dispatch"), nothing in this file.
"""
import json
import re
from pathlib import Path

MAX_OPCODE = 0xA7

SCRIPT_TABLE_ADDR = 0x0805B978
SCRIPT_COUNT = 65  # 0x41 -- confirmed by g_apEffectScripts' bounds check
SCRIPT_DATA_START = 0x0805994C  # first script's pointer; scripts are
                                 # packed contiguously right up to SCRIPT_TABLE_ADDR

# A script's file gets included as a real assembler label
# (pack_objscript.py emits it as `<name>:`), so its name must be a
# valid, unambiguous identifier.
NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

_OPCODES_JSON = json.loads((Path(__file__).parent / "opcodes.json").read_text())["opcodes"]

# opcode number -> name, name -> opcode number, opcode number -> operand byte count
OPCODE_NAME_BY_NUMBER: dict[int, str] = {int(k): v["name"] for k, v in _OPCODES_JSON.items()}
OPCODE_NUMBER_BY_NAME: dict[str, int] = {v: k for k, v in OPCODE_NAME_BY_NUMBER.items()}
OPCODE_OPERAND_LENGTH: dict[int, int] = {int(k): v["operand_length"] for k, v in _OPCODES_JSON.items()}

# opcode number -> {"operand_index": int, "cases": {sub-case value: name}},
# for opcodes (currently just StatusEffect/0x97) whose own operand bytes
# select a further sub-case -- see opcodes.json. Used only to annotate
# the curated text format with a readability comment; never affects
# encode/decode.
OPCODE_SUB_DISPATCH: dict[int, dict] = {
    int(k): v["sub_dispatch"] for k, v in _OPCODES_JSON.items() if "sub_dispatch" in v
}

_GENERIC_NAME_RE = re.compile(r"^opcode_([0-9A-Fa-f]{2})$")


def opcode_name(opcode: int) -> str:
    return OPCODE_NAME_BY_NUMBER.get(opcode, f"opcode_{opcode:02X}")


def opcode_number(name: str) -> int:
    """Reverse of opcode_name(): resolves a name back to its opcode number.
    Accepts either a curated name from opcodes.json or the generic
    "opcode_XX" fallback form (even for opcodes that do have a curated
    name -- the numeric form always works, same as real assemblers
    accept a raw opcode alongside a mnemonic)."""
    if name in OPCODE_NUMBER_BY_NAME:
        return OPCODE_NUMBER_BY_NAME[name]
    m = _GENERIC_NAME_RE.match(name)
    if m:
        return int(m.group(1), 16)
    raise ValueError(f"unknown opcode name {name!r}")


def decode_script(data: bytes) -> list[tuple[int, bytes]]:
    """Splits a raw script byte string into (opcode, operand_bytes) pairs."""
    instructions = []
    pos = 0
    while pos < len(data):
        opcode = data[pos]
        length = OPCODE_OPERAND_LENGTH[opcode] + 1
        instructions.append((opcode, data[pos + 1:pos + length]))
        pos += length
    if pos != len(data):
        raise ValueError(f"script decode overran its bounds: ended at {pos}, expected {len(data)}")
    return instructions


def encode_script(instructions: list[tuple[int, bytes]]) -> bytes:
    out = bytearray()
    for opcode, operands in instructions:
        expected = OPCODE_OPERAND_LENGTH[opcode]
        if len(operands) != expected:
            raise ValueError(f"opcode {opcode:#x} expects {expected} operand byte(s), got {len(operands)}")
        out.append(opcode)
        out.extend(operands)
    return bytes(out)


def format_script_text(instructions: list[tuple[int, bytes]]) -> str:
    """Renders instructions in the curated per-effect text format:
    one instruction per line, "<name> [operand operand ...]" (decimal
    operands), using each opcode's current name from opcodes.json. If
    the opcode has a named sub-dispatch case (StatusEffect's own
    sub-case byte, see OPCODE_SUB_DISPATCH) matching the relevant
    operand, appends "# <sub-case name>" as a read-only comment --
    parse_script_text ignores it, same as any other trailing comment."""
    lines = []
    for opcode, operands in instructions:
        parts = [opcode_name(opcode)] + [str(b) for b in operands]
        line = " ".join(parts)
        sub = OPCODE_SUB_DISPATCH.get(opcode)
        if sub is not None and len(operands) > sub["operand_index"]:
            sub_value = str(operands[sub["operand_index"]])
            sub_name = sub["cases"].get(sub_value)
            if sub_name is not None:
                line += f"  # {sub_name}"
        lines.append(line)
    return "\n".join(lines) + "\n"


def parse_script_text(text: str) -> list[tuple[int, bytes]]:
    """Inverse of format_script_text(). Blank lines, lines starting with
    '#', and trailing '# ...' comments are ignored."""
    instructions = []
    for lineno, raw_line in enumerate(text.splitlines(), 1):
        line = raw_line.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        try:
            opcode = opcode_number(parts[0])
            operands = bytes(int(tok) for tok in parts[1:])
        except ValueError as e:
            raise ValueError(f"line {lineno}: {e} ({raw_line!r})") from e
        instructions.append((opcode, operands))
    return instructions
