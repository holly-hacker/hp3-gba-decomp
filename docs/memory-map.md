# Memory map / binary layout notes

## Confidence key

Findings below are marked:

- **PROVEN** — directly verifiable fact (string bytes, instruction bytes,
  cross-referenced addresses). Re-running the same disassembly/search will
  reproduce it.
- **STRUCTURAL MATCH** — behavior/shape observed in disassembly matches a
  documented Krawall API function or convention closely, but is not
  confirmed against exact source, so the specific name (e.g. "kramWorker")
  is a working label, not a proven identity.
- **UNCONFIRMED** — plausible but with no independent corroboration found
  yet; flagged explicitly so it doesn't get mistaken for something stronger.

## Krawall audio engine — confirmed, located

CLAUDE.md already assumed Krawall (LGPL, https://github.com/sebknzl/krawall)
based on general knowledge of this game. Confirmed directly in the ROM:

### Version string (proof of direct source use, not a reimplementation)

A CVS/RCS `$Id$` keyword tag from the Krawall source is embedded verbatim in
both ROMs:

```
$Id: Krawall $Date: 2003/09/01 06:51:01 $
```

- US (`baserom.us.gba`): file offset `0xFA9541` (ROM address `0x08FA9541`)
- JP (`baserom.jp.gba`): file offset `0xF3C9CC` (ROM address `0x08F3C9CC`)

Identical string, identical date, in both versions — confirms a single
shared Krawall revision compiled into both ROM builds. Because the tag
compiles down from a literal `static const char rcsid[] = "$Id: ...$"` in
the original source, this proves the actual Krawall source was compiled in
(not reimplemented from scratch), and pins the exact upstream revision date
(2003-09-01) — useful for pulling a matching snapshot of the Krawall repo
history to diff against once we start decompiling the driver.

The string sits inside what looks like a small data blob/struct (pointers to
nearby offsets follow it — see below), not a lone dead string, so it's part
of a real linked data structure, not editor debris.

### Pointer table referencing the version blob

Three literal-pool references to the region right after the version string
were found (pointing at `0x08FA95A8`, offset `+0x67` from the string start):

- `0x08047994` and `0x08047A40` — both inside the same function-pair
  described below.
- `0x00FB1E10` — a third reference elsewhere in the ROM, not yet chased.

### Likely driver API call site

The code at `0x08047994`–`0x08047A36` (Thumb) and its sibling starting at
`0x08047A40` iterate a struct array (element size `0x60` bytes, per-channel
data judging by the loop shape) and, for populated entries, call three
tightly-clustered small functions:

- `0x0804A2C8`
- `0x0804A2CC`
- `0x0804A2D0`

These being only 4 bytes apart and called with matching `(ptr, flag)`-style
argument patterns is consistent with adjacent entries in Krawall's public
mixer API — see below for why this is a structural guess, not a confirmed
match.

### Public Krawall source pulled for reference — NOT a byte-level match

Cloned https://github.com/sebknzl/krawall (LGPL, kept in scratch space only,
never vendored into this repo per the licensing note in CLAUDE.md). Findings
that matter for how we can use it:

- The repo's git history starts at commit `878a821` / `9a2b869`, dated
  **2013-07-13/18** — a decade after the `2003/09/01` `$Id` revision date
  embedded in our ROM.
- None of the current source files carry `$Id` CVS keyword tags at all
  (checked `lib/*.h`, `lib/*.c`) — the public release doesn't use CVS
  keyword substitution the way the compiled ROM clearly does. This confirms
  (not just suspects) it's a restructured/later snapshot (tagged version
  `1.0.0`, copyright `2001-2005, 2013`), not the CVS tree this game was
  built from.
- **Conclusion: no byte-level diff/match is possible against this source.**
  It's useful only as an API-shape/naming reference, not for confirming
  exact function boundaries or struct layouts, and not for the
  "diff against known source to skip decompiling" shortcut floated earlier.

What it *is* useful for: `lib/mixer.h` exposes a `chandle`-based API —
`kramStop(chandle)`, `kramSetFreq(chandle, freq)`, `kramSetVol(chandle, vol)`,
`kramSetPan(chandle, pan)`, `kramActive(chandle)`, `kramWorker()`, etc. All
the per-channel setters take `(handle, value)` — this matches the
`(ptr, flag/value)` call shape seen at the three clustered call sites
(`0x0804A2C8`–`0x0804A2D0`), which is corroborating-but-not-confirming
evidence that these are `kramSet*`/`kramStop`/`kramActive`-family calls.
Which three specifically is still unconfirmed.

## Candidate kramWorker() and inner mixer routine

Chased the third pointer reference (`0x00FB1E10`, a table of ROM/EWRAM/IWRAM
pointers immediately preceding an ARM-mode function) and found a strongly
plausible pair of core engine functions, both ARM-mode, right after the
Krawall version-string data blob:

### `0x08FB1E18` — candidate `kramWorker()` [STRUCTURAL MATCH]

APCS frame-pointer prologue (`mov ip, sp` / `push {r4,r5,r6,fp,ip,lr,pc}`),
matching epilogue (`ldmdb fp, {r4,r5,r6,fp,sp,lr}` / `bx lr`). Behavior:

1. Calls a Thumb-mode function at `0x08046E0C` (via `mov lr,pc; bx r2`
   interworking call) passing two stack out-params (`[fp-0x1c]`,
   `[fp-0x20]`) — plausibly a "get current write pointer" callback,
   returning a requested/needed sample count in r0/r4.
2. Compares that count against a running value at EWRAM `0x0200163E`
   (halfword) — call it `avail`.
3. **If `avail > requested`** (enough contiguous space): one call into
   `0x08FB19F8` with the full requested count, decrement `avail` by that
   amount, return 1 (success/did-work).
4. **If `avail <= requested`** (not enough contiguous space — buffer
   wraparound case): checks a function pointer at EWRAM `0x02001638`
   (null-checked, then actually *called* later in this same path — so
   `0x02001638` holds a callback, not a flag); fills the first chunk via
   `0x08FB19F8`, advances the two output pointers by the consumed amount,
   decrements the remaining requested count, invokes the `0x02001638`
   callback again (presumably a "wrapped to buffer start" notification),
   reloads a buffer-size constant from EWRAM `0x0200163C` into the `avail`
   counter (`0x0200163E`) — i.e. resets available-space after wrapping —
   and loops back to fill the remainder.
5. Return value is `0` (nothing to do, taken when the very first callback
   returns a 0 request count) or `1` (did work) — a plausible
   `int kramWorker()`-style status return.

This is a genuine ring-buffer wraparound refill loop, which is more
specific and more internally consistent than a generic "buffer feed" shape
— strengthens the case this is `kramWorker()` or its direct equivalent.
**Caveat**: which register/global holds "available space" vs "requested
amount" is inferred from control flow, not verified by running the code
(no emulator/debugger session was used) — the mechanics (branch structure,
the second callback invocation, the constant reload) are read directly off
real instructions, but the semantic labels attached to each value are best
judged as reasonable inference, not fact, until checked dynamically.

**EWRAM engine-state globals found so far**: `0x02001638` (callback
function pointer, invoked on buffer wrap), `0x0200163C` (u16, buffer-size
constant), `0x0200163E` (u16, available-space counter). Worth grouping into
a `KramEngineState`-style struct once more fields are found.

### `0x08FB19F8` — candidate inner mixer / channel-scan routine [PROVEN mechanics / STRUCTURAL MATCH interpretation]

The loop mechanics themselves (32 iterations, `+0x2C` stride, status-byte
check at `+2`) are read directly off real instructions — reproducible by
disassembling this address. The *interpretation* ("this is a channel array
scan for active channels") is inference from that shape, not confirmed
against source.

Also APCS-framed, saves the full `r4-r11` register set (heavier frame than
`kramWorker`, consistent with being the actual hot per-sample/per-channel
path). Behavior: iterates what looks like a **32-channel array**
(`mov sb, #0x20` = 32, decrementing loop counter) with **`0x2C` (44)-byte
stride per element**, checking a status byte at **offset `+2`** of each
channel struct to find active channels, then dispatches into per-channel
mixing via a further `bx` call. 32 channels matches typical GBA audio-engine
scale (Krawall's public API talks in terms of a fixed channel pool); the
44-byte stride and offset-2 status byte are concrete candidate fields for a
future `KramChannel` struct.

Not yet confirmed whether this or a callee is IWRAM-resident at runtime (may
be DMA'd/copied into IWRAM at init rather than linked there directly — worth
checking the EWRAM/IWRAM copy step in the init flow once we look at that).

### Cross-referencing the pointer table at 0xFB1DF4–0xFB1E14 [mixed confidence]

The 7-word table immediately preceding `kramWorker`'s candidate address
(`0x03000AFC`, `0x03001144`, `0x020008B4`, `0x03000B38`, `0x03000B30`,
`0x03000B34`, `0x08FA9568`, `0x03000AB4`) was checked for independent
references elsewhere in the ROM (literal 4-byte search, whole ROM):

- **`0x020008B4`** (EWRAM) — **PROVEN heavily used**: 20 independent
  references, clustered in `0x46E00`–`0x47200`, i.e. inside the same
  channel-dispatch code region documented above (`0x08047994`/`0x08047A40`).
  Strong evidence `0x46000`–`0x48000` and `0xFB19F0`–`0xFB1EE0` are one
  cohesive Krawall driver code block, and that this address is a real,
  important shared global (likely channel-array base or context pointer).
- **`0x03000AB4`** (IWRAM) — **PROVEN independently referenced**: appears
  once in the table and once more at `0x0473B0`, also inside that same code
  cluster. Confirms this is a real, meaningfully-used address, not table
  noise.
- **`0x03000AFC`, `0x03001144`, `0x03000B38`, `0x03000B30`, `0x03000B34`** —
  **UNCONFIRMED**: each appears *only* inside this one table, nowhere else
  in the ROM as a literal. This doesn't disprove the "IWRAM code-relocation
  table" theory (code could load these dynamically from the table at
  runtime rather than hardcoding each one separately as an immediate), but
  it means these five have no independent corroboration yet. Do not treat
  them as confirmed IWRAM call targets — flagging explicitly per instruction
  to be confident, not just plausible, before asserting a match.

## Next steps

- [ ] Do NOT expect the public Krawall repo to resolve function identity by
      diffing — it's a different source revision. Naming these functions
      will require either behavioral/structural inference from disassembly,
      or finding an actual 2003-era Krawall source snapshot if one exists
      (unlikely to be publicly available).
- [ ] Trace the Thumb "query free space" callback at `0x08046E0C`.
- [ ] Confirm whether `0x08FB19F8` (or a callee) gets copied to IWRAM at
      startup, per Krawall's documented perf requirement for the mixer.
- [ ] Map more fields of the candidate `KramEngineState` (EWRAM
      `0x02001638`-`0x0200163E`) and `KramChannel` (44-byte stride, status
      byte at `+2`) structs.
- [ ] Once functions are named (via inference, not source diff), begin
      populating `symbols.us.txt`.
