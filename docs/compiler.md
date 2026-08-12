# Compiler fingerprinting

Status: **fairly confident, not yet fully proven** — two independent
structural signals both point to ARM ADS/RVCT (armcc), not GCC/agbcc. Still
short of a byte-level reference match, so treat as strong-but-not-final per
CLAUDE.md hard rule 4 (verify, don't assume) until a reference binary or
signature database confirms it.

## Method

ROM entry point (US, `baserom.us.gba`, sha1 `5be308501f0cfe0c30c60ef1fbf886707cdacd29`):

- Header branch at `0x08000000` targets `0x080000C0`.
- `0x080000C0`–`0x08000268`: mode/stack setup (IRQ/SVC/System) then an
  `IntrMain`-style interrupt dispatcher that walks `IE`/`IF` bit-by-bit,
  incrementing a jump-table pointer per flag. This pattern is shared
  boilerplate seen across many licensed GBA titles regardless of compiler
  (likely derived from Nintendo SDK sample code), so it is **not** diagnostic
  on its own.
- `0x0800027C`–`0x080002E0`: signed division wrapper — computes abs(r0),
  abs(r1), xors the sign bits, calls the unsigned divide at `0x080002E0`,
  then negates the result if signs differed. This sign-handling wrapper
  pattern is common to many runtimes and also not diagnostic alone.
- `0x080002E0` onward: the unsigned divide itself. This **is** diagnostic.

## Finding: unsigned divide routine at 0x080002E0

Disassembly is a **32-way binary-search branch tree**: a cascade of
`cmp r1, r0, lsr #N` / `bhi` instructions, one per bit position (starting
`lsr #15`, then `lsr #23`, `#27`, `#29`, `#30`... narrowing down to the exact
bit-length of the dividend before dispatching to a bit-specific division
handler). This costs several hundred bytes of code for a routine that in
agbcc/GCC (`__udivsi3`) is normally a compact ~15-20 instruction
shift-and-subtract loop.

This binary-search-tree division shape matches **ARM's own compiler runtime
library** (ADS / RVCT `armcc`, i.e. `_uidiv`/`__rt_udiv`-family routines),
**not** GCC's `__udivsi3`.

## Finding: paired div/mod wrappers at 0x0800027C and 0x080002A4

Immediately before the unsigned divide, there are two back-to-back signed
wrapper functions, both computing `abs(r0)`, `abs(r1)`, and a sign-xor, then
calling the shared unsigned divide at `0x080002E0`.

- `0x0800027C`: plain signed divide. Negates r0 (quotient) per the sign flag,
  returns quotient only in r0.
- `0x080002A4`: signed **divide-and-modulo**. Before calling, it
  `stmdb sp!, {r2}` — i.e. the caller passes a pointer to a remainder cell
  *in r2*. After the divide call it negates both the quotient (r0) and the
  remainder (r1) per their respective sign bits, then `str r1, [r2]` —
  writing the remainder out through that pointer parameter, returning only
  the quotient in r0.

Returning the remainder via an out-parameter pointer (rather than in a
register, and rather than as a wholly separate `__modsi3`-style function) is
the classic **ARM ADS/RVCT `__rt_sdiv`-family calling convention**. GCC's
`__divsi3`/`__modsi3`/`__udivmodsi4` never use a pointer-out-parameter for
the remainder. This is a second, structurally independent signal (distinct
from the branch-tree divide algorithm) and it agrees with the first.

## Working hypothesis

**This ROM was compiled with ARM ADS/RVCT (`armcc`), not GCC/agbcc.** Two
independent structural signatures (binary-search division algorithm;
pointer-out-parameter div/mod calling convention) both point this direction.
This changes the toolchain plan in CLAUDE.md's "Target toolchain" section —
the agbcc-fork path (à la kl-eod-decomp) likely does not apply; we'd instead
be looking at ADS/RVCT-compatible tooling or a modern Clang/`armclang`-based
matching approach.

## Things checked that were inconclusive (not contradicting)

- **Scatterload search**: traced the ARM-mode crt0 (`0x080000C0`–`0x08000268`,
  mode/stack setup + IRQ vector install) through its Thumb-mode entry
  trampoline (`0x080000EC`), which loads a function pointer from a literal
  pool (`0x08029691`, i.e. `0x08029690` + Thumb bit) and calls it directly.
  That target looks like game-specific init code (masking IRQ bits, then
  ~30 `bl`s into subsystem-init functions) with no visible RW-data-copy or
  BSS-zero loop beforehand. Could mean scatterloading happens elsewhere, or
  isn't needed the way expected — inconclusive either way, not worth
  chasing further given the two solid confirmations above.

## Next steps to fully confirm

- [ ] Byte-level comparison against a known ADS/RVCT-compiled reference
      binary's division routine, if one can be sourced (e.g. another
      EA-published GBA title with a documented compiler, or a from-scratch
      armcc-compiled test binary). This is the actual proof step — current
      evidence is strong on algorithm/convention shape but not a byte match.
- [ ] IDA/Ghidra RVCT/ADS runtime-library signature packs (FLIRT-style), if
      available, would auto-confirm.
- [ ] Re-run the same checks against `baserom.jp.gba` to confirm both
      versions share a toolchain (expected, but verify).
