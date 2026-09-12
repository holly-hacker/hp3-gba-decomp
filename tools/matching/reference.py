"""Extract relocatable reference assembly; preparation verifies it against ROM bytes."""
import re
from .workspace import ROOT

FUNC_START_RE = re.compile(r"^\s*(thumb|arm)_func_start\s+(\S+)")
LITERAL_RE = re.compile(r"^(\s*(?:\w+:\s*)?)\.4byte\s+(0[xX][0-9a-fA-F]+)\s*(?:@.*)?$")

def ram_symbols(ver: str) -> dict[int, str]:
    out = {}
    path = ROOT / f"ram_symbols.{ver}.inc"
    if not path.exists():
        return out
    for line in path.read_text().splitlines():
        m = re.match(r"^\.set\s+(\S+?),\s*(0[xX][0-9a-fA-F]+)", line)
        if m:
            address, name = int(m.group(2), 16), m.group(1)
            if address in out and out[address] != name:
                raise ValueError(f"{path}: duplicate .set for {address:#x}: {out[address]}, {name}")
            out[address] = name
    return out


def build_target_asm(ver: str, name: str, end_address: int | None = None) -> tuple[str, str]:
    """Returns (asm_text, 'arm'|'thumb')."""
    path = ROOT / f"build/{ver}/full_disasm.s"
    if not path.exists():
        raise ValueError(f"{path} missing -- run `just disasm-compare {ver}` first")
    lines = path.read_text().splitlines(keepends=True)
    starts = [(i, mode, fname) for i, l in enumerate(lines)
              if (m := FUNC_START_RE.match(l))
              for mode, fname in [(m.group(1), m.group(2))]]
    idx = next((i for i, (_, _, n) in enumerate(starts) if n == name), None)
    if idx is None:
        raise ValueError(f"{name!r} not found as a func_start label in {path}")
    begin, mode, _ = starts[idx]
    end = starts[idx + 1][0] if idx + 1 < len(starts) else len(lines)
    if end_address is not None:
        # A data/branch label may mark the complete extent before the next seed.
        # Never truncate an instruction or data directive merely to hit the size.
        for i in range(begin + 1, end):
            label = re.match(r"^_([0-9A-Fa-f]{8}):", lines[i])
            annotated = re.match(r"^\w+:\s*@\s*(0x[0-9A-Fa-f]+)", lines[i])
            address = int(label[1], 16) if label else int(annotated[1], 16) if annotated else None
            if address == end_address:
                end = i
                break
    body = lines[begin + 1:end]  # skip the func_start directive itself

    symbols = ram_symbols(ver)
    externs, out = set(), []
    for line in body:
        m = LITERAL_RE.match(line)
        if m and int(m.group(2), 16) in symbols:
            sym = symbols[int(m.group(2), 16)]
            externs.add(sym)
            out.append(f"{m.group(1)}.4byte {sym}\n")
        else:
            out.append(line)

    macro = "arm" if mode == "arm" else "thumb"
    header = "".join(f".extern {s}\n" for s in sorted(externs))
    header += (
        ".syntax unified\n"
        f".align 2, 0\n.global {name}\n.{macro}\n"
        + (".thumb_func\n" if macro == "thumb" else "")
        + f".type {name}, %function\n{name}:\n"
    )
    footer = f".size {name}, .-{name}\n"
    return header + "".join(out) + footer, macro
