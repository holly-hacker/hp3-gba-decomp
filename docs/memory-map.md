# Memory map / binary layout notes

This used to be one long document; it's now split by subsystem so each part
stays a manageable size. This file is just the shared confidence-key
legend and an index.

## Confidence key

Findings in both documents below are marked:

- **PROVEN** — directly verifiable fact (string bytes, instruction bytes,
  cross-referenced addresses). Re-running the same disassembly/search will
  reproduce it.
- **STRUCTURAL MATCH** — behavior/shape observed in disassembly matches a
  documented Krawall API function or convention closely, but is not
  confirmed against exact source, so the specific name (e.g. "kramWorker")
  is a working label, not a proven identity.
- **UNCONFIRMED** — plausible but with no independent corroboration found
  yet; flagged explicitly so it doesn't get mistaken for something stronger.

## Documents

- [`memory-map/krawall.md`](memory-map/krawall.md) — the Krawall audio
  engine: locating it in the ROM, the mixer/effect-handler driver code,
  `KramChannel`/`MixChannel` struct fields, the IWRAM/EWRAM install
  mechanism, and cross-referencing findings against the public Krawall
  source. Includes the "Next steps" checklist and the dropped gdb-stub
  dynamic-verification attempt.
- [`memory-map/rng.md`](memory-map/rng.md) — the game's RNG: jogotu's
  (Harry Potter Handheld Speedrunning Discord) BizHawk script findings on
  the MT19937 state layout, battle/fighter structs, and hit/crit formulas,
  plus the confirmed-in-disasm MT19937 function cluster and its two
  independent draw cursors.
- [`memory-map/battle.md`](memory-map/battle.md) — the `BattleFighter`
  struct and the traced attack-resolution/damage-application functions
  (hit/miss, base damage, defense scaling, the "Be More Careful"-style
  damage-halving flags, a crit-style bonus-damage roll), built from leads
  contributed by jlun2 and cross-checked against our own disassembly.
