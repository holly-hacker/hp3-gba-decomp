"""Shared format knowledge for the room-script bytecode VM
(`WalkRoomSwitchStateChain_candidate`, US `0x08005410`). See
docs/formats/room_scripts.md for how each constant below was identified.

Byte format, distinct from battle_scripts_codec.py's: each instruction's
opcode is a full `u32` (not a `u8`), followed by
`g_abRoomScriptOpcodeLengths[opcode] - 4` operand bytes. Opcode `0`
(`End`) terminates a chain with no operands and no handler call.

Opcode metadata lives in opcodes.json next to this file (name,
operand_length in bytes, optional operand_widths breaking those bytes
into wider little-endian fields for readability, optional
comment_source for annotating one decoded operand with a read-only
trailing comment -- currently just `ShowRoomDialog`'s dialog-text id).
Committed rather than gitignored, same footing as
battle_scripts/opcodes.json: interpreter/ISA knowledge, not extracted
game content, and deliberately carries no addresses (see
battle_scripts_codec.py's module docstring for why).

Two more optional per-opcode arrays, only present for opcodes whose
fields are actually identified: `operand_names` (one label per decoded
value, e.g. "x"/"y"/"bit") and `operand_defaults` (that value's default,
or `null` if it must always be written explicitly). A value equal to
its default is dropped from the curated text's trailing run -- only a
*contiguous run from the end* is ever hidden, so position is never
ambiguous -- and format_chain_text renders every kept value as
"name:value" instead of a bare number. A default is only ever set on a
byte confirmed unread by that opcode's handler (real padding, e.g. the
trailing bytes battle_scripts.md-style comparator opcodes leave
unused) or, for `ShowRoomDialog`'s two trailing bytes, confirmed
*always* `0` in every extracted script -- never merely "every example
we happen to have looks the same" for a field the handler does read
and could vary. parse_chain_text fills any omitted trailing values back
in from operand_defaults, and still accepts them written out
explicitly (with or without the "name:" label) if a curator wants them
visible.

This VM has no `data/` pipeline yet (see room_scripts.md and
dump_room_scripts.py's docstring) -- the room table isn't itself a
regions.<ver>.txt region yet, so there is nothing to pack back into.
This module's decode/format half is shared with a future pack step
regardless, same as every other subsystem's codec.

Per-chain identification (which room-script chain does what) lives in
script_names.json next to this file, same footing/role as
battle_scripts/script_names.json: curated RE knowledge, committed even
though data/room_scripts/ itself is gitignored. Nested by room index
then chain index as strings (there is no single flat id space like
battle scripts' effect id, since chains are scoped per room), each leaf
optionally carrying "name" (used in the chain's extracted filename by
extract_room_scripts.py in place of the default "chain<N>") and
"description" (emitted as a leading "# ..." comment by
format_chain_text -- purely informational, stripped by
parse_chain_text like any other comment).
"""
import json
import re
from pathlib import Path

_OPCODES_JSON = json.loads((Path(__file__).parent / "opcodes.json").read_text())["opcodes"]

OPCODE_NAME_BY_NUMBER: dict[int, str] = {int(k): v["name"] for k, v in _OPCODES_JSON.items()}
OPCODE_NUMBER_BY_NAME: dict[str, int] = {v: k for k, v in OPCODE_NAME_BY_NUMBER.items()}
OPCODE_OPERAND_LENGTH: dict[int, int] = {int(k): v["operand_length"] for k, v in _OPCODES_JSON.items()}
# opcode number -> list of byte-widths (1/2/4) the operand bytes split into,
# each read/written little-endian. Opcodes without an explicit entry are
# treated as all-byte-width (one operand token per byte), matching
# battle_scripts_codec.py's convention.
OPCODE_OPERAND_WIDTHS: dict[int, list[int]] = {
    int(k): v["operand_widths"] for k, v in _OPCODES_JSON.items() if "operand_widths" in v
}
# opcode number -> {"type": "dialog_text", "value_index": int}: which
# decoded operand value (index into the widths-split list) is a dialog
# string id, for a "# ..." readability comment. Never affects decode/encode.
OPCODE_COMMENT_SOURCE: dict[int, dict] = {
    int(k): v["comment_source"] for k, v in _OPCODES_JSON.items() if "comment_source" in v
}
# opcode number -> one label per decoded value (parallel to operand_widths()).
OPCODE_OPERAND_NAMES: dict[int, list[str]] = {
    int(k): v["operand_names"] for k, v in _OPCODES_JSON.items() if "operand_names" in v
}
# opcode number -> one default per decoded value (None = no default, must be
# written explicitly). See this module's docstring for what qualifies.
OPCODE_OPERAND_DEFAULTS: dict[int, list[int | None]] = {
    int(k): v["operand_defaults"] for k, v in _OPCODES_JSON.items() if "operand_defaults" in v
}

_GENERIC_NAME_RE = re.compile(r"^opcode_([0-9A-Fa-f]{2})$")

MAX_OPCODE = max(OPCODE_NAME_BY_NUMBER)

_SCRIPT_NAMES_JSON = json.loads((Path(__file__).parent / "script_names.json").read_text())["scripts"]

# "<room index>:<chain index>" -> curated name/description, for the chains
# we're confident about the real-world purpose of. Absent entries just
# mean "not yet identified" -- extract_room_scripts.py falls back to
# "chain<N>". Flattened here from script_names.json's room-then-chain
# nesting so the rest of this module (and extract_room_scripts.py) only
# ever deals with one flat key per chain.
SCRIPT_NAME_BY_KEY: dict[str, str] = {}
SCRIPT_DESCRIPTION_BY_KEY: dict[str, str] = {}
for _room_idx, _chains in _SCRIPT_NAMES_JSON.items():
    for _chain_idx, _entry in _chains.items():
        _key = f"{_room_idx}:{_chain_idx}"
        if "name" in _entry:
            SCRIPT_NAME_BY_KEY[_key] = _entry["name"]
        if "description" in _entry:
            SCRIPT_DESCRIPTION_BY_KEY[_key] = _entry["description"]


def script_key(room_idx: int, chain_idx: int) -> str:
    return f"{room_idx}:{chain_idx}"


# A curated chain name becomes a filename (extract_room_scripts.py) --
# keep it a plain identifier, same constraint battle_scripts_codec.py's
# NAME_RE applies to its (assembly-label) filenames, even though this VM
# has no assembly-label use for it yet.
NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def opcode_name(opcode: int) -> str:
    return OPCODE_NAME_BY_NUMBER.get(opcode, f"opcode_{opcode:02X}")


def opcode_number(name: str) -> int:
    if name in OPCODE_NUMBER_BY_NAME:
        return OPCODE_NUMBER_BY_NAME[name]
    m = _GENERIC_NAME_RE.match(name)
    if m:
        return int(m.group(1), 16)
    raise ValueError(f"unknown opcode name {name!r}")


def operand_widths(opcode: int) -> list[int]:
    if opcode in OPCODE_OPERAND_WIDTHS:
        return OPCODE_OPERAND_WIDTHS[opcode]
    return [1] * OPCODE_OPERAND_LENGTH[opcode]


def split_operand_values(opcode: int, operand_bytes: bytes) -> list[int]:
    """Groups raw operand bytes into the wider little-endian fields
    operand_widths() declares (default: one value per byte)."""
    widths = operand_widths(opcode)
    values = []
    pos = 0
    for w in widths:
        values.append(int.from_bytes(operand_bytes[pos:pos + w], "little"))
        pos += w
    return values


def join_operand_values(opcode: int, values: list[int]) -> bytes:
    widths = operand_widths(opcode)
    if len(values) != len(widths):
        raise ValueError(f"opcode {opcode:#x} expects {len(widths)} operand value(s), got {len(values)}")
    out = bytearray()
    for value, w in zip(values, widths):
        out += value.to_bytes(w, "little")
    return bytes(out)


def decode_chain(data: bytes, base_offset: int = 0) -> list[tuple[int, bytes]]:
    """Splits a raw room-script chain into (opcode, operand_bytes) pairs,
    starting at data[base_offset:] and stopping after opcode 0 (End)."""
    instructions = []
    pos = base_offset
    while True:
        opcode = int.from_bytes(data[pos:pos + 4], "little")
        length = OPCODE_OPERAND_LENGTH[opcode]
        instructions.append((opcode, data[pos + 4:pos + 4 + length]))
        pos += 4 + length
        if opcode == 0:
            break
    return instructions


def encode_chain(instructions: list[tuple[int, bytes]]) -> bytes:
    out = bytearray()
    for opcode, operands in instructions:
        expected = OPCODE_OPERAND_LENGTH[opcode]
        if len(operands) != expected:
            raise ValueError(f"opcode {opcode:#x} expects {expected} operand byte(s), got {len(operands)}")
        out += opcode.to_bytes(4, "little")
        out += operands
    return bytes(out)


def _sanitize_comment_text(text: str) -> str:
    return text.replace("\\", "\\\\").replace("\n", "\\n").replace("\r", "")


def format_chain_text(instructions: list[tuple[int, bytes]], resolve_comment=None, description: str | None = None) -> str:
    """Renders instructions in the curated per-chain text format: one
    instruction per line, "<name> [value value ...]" (decimal values,
    grouped per operand_widths()). If the opcode has a comment_source
    and resolve_comment is given, calls
    resolve_comment(comment_source, values) -> list[str] | None; each
    returned string becomes its own "# ..." comment line immediately
    before the instruction (e.g. one line per line of ShowRoomDialog's
    decoded dialog text, rather than cramming a whole multi-line block
    onto one trailing comment).

    If description is given (see SCRIPT_DESCRIPTION_BY_KEY), it's
    emitted as a leading "# <description>" comment line -- purely
    informational, same round-trip guarantee as the per-instruction
    comments above."""
    lines = []
    if description:
        lines.append(f"# {description}")
    for opcode, operand_bytes in instructions:
        values = split_operand_values(opcode, operand_bytes)
        source = OPCODE_COMMENT_SOURCE.get(opcode)
        if source is not None and resolve_comment is not None:
            comment_lines = resolve_comment(source, values)
            if comment_lines is not None:
                lines.extend(f"# {_sanitize_comment_text(c)}" for c in comment_lines)
        names = OPCODE_OPERAND_NAMES.get(opcode)
        defaults = OPCODE_OPERAND_DEFAULTS.get(opcode)
        if names is not None:
            kept = len(values)
            if defaults is not None:
                while kept > 0 and defaults[kept - 1] is not None and values[kept - 1] == defaults[kept - 1]:
                    kept -= 1
            tokens = [f"{names[i]}:{values[i]}" for i in range(kept)]
        else:
            tokens = [str(v) for v in values]
        lines.append(" ".join([opcode_name(opcode)] + tokens))
    return "\n".join(lines) + "\n"


def _parse_operand_token(token: str, expected_name: str | None) -> int:
    """Parses one operand token, either a bare "123" or a labeled
    "name:123". If expected_name is given (the opcode has operand_names),
    a labeled token's name must match it -- catches a curator reordering
    or miscounting values by hand."""
    if ":" in token:
        label, _, value_s = token.partition(":")
        if expected_name is not None and label != expected_name:
            raise ValueError(f"expected operand {expected_name!r}, got {label!r}")
        return int(value_s)
    return int(token)


def parse_chain_text(text: str) -> list[tuple[int, bytes]]:
    """Inverse of format_chain_text(): blank lines and '#' comments
    (leading or trailing) are ignored. Operand tokens may be bare
    ("123") or labeled ("name:123", format_chain_text's own output);
    trailing values omitted because they matched their operand_defaults
    are filled back in."""
    instructions = []
    for lineno, raw_line in enumerate(text.splitlines(), 1):
        line = raw_line.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        try:
            opcode = opcode_number(parts[0])
            names = OPCODE_OPERAND_NAMES.get(opcode)
            defaults = OPCODE_OPERAND_DEFAULTS.get(opcode)
            tokens = parts[1:]
            expected = len(operand_widths(opcode))
            if names is not None and len(tokens) < expected:
                if defaults is None:
                    raise ValueError(f"opcode {opcode_name(opcode)} expects {expected} operand value(s), got {len(tokens)}")
                for i in range(len(tokens), expected):
                    if defaults[i] is None:
                        raise ValueError(f"opcode {opcode_name(opcode)} operand {names[i]!r} has no default, must be given")
                values = [_parse_operand_token(tok, names[i] if names else None) for i, tok in enumerate(tokens)]
                values += [defaults[i] for i in range(len(tokens), expected)]
            else:
                values = [_parse_operand_token(tok, names[i] if names else None) for i, tok in enumerate(tokens)]
            operands = join_operand_values(opcode, values)
        except ValueError as e:
            raise ValueError(f"line {lineno}: {e} ({raw_line!r})") from e
        instructions.append((opcode, operands))
    return instructions
