# Memory map / binary layout notes

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

## Next steps

- [ ] Do NOT expect the public Krawall repo to resolve function identity by
      diffing — it's a different source revision. Naming these functions
      will require either behavioral/structural inference from disassembly,
      or finding an actual 2003-era Krawall source snapshot if one exists
      (unlikely to be publicly available).
- [ ] Chase the third pointer reference at `0x00FB1E10`.
- [ ] Identify the actual mixer/IRQ-driven playback routine (likely IWRAM,
      per Krawall's documented performance requirement) — not yet located;
      the code found so far looks like higher-level channel/SFX dispatch,
      not the low-level sample mixer itself.
- [ ] Once functions are named (via inference, not source diff), begin
      populating `symbols.us.txt`.
