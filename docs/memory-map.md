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

### Full disassembly of `kramWorker_MixChannels`, and the 44-byte channel struct [PROVEN mechanics, STRUCTURAL MATCH interpretation]

`gbadisasm` only disassembles part of this function -- it treats the
mid-function `bx r2` at `0x08FB1A24` (an indirect call, not a return) as a
function boundary and dumps everything after it as raw `.byte`s. Read the
whole thing with `objdump -b binary -m arm` over
`0x08FB19F8`-`0x08FB1E18` instead (outside the manifest/build, pure
discovery -- see the `disasm ver="us"` comment for why `gbadisasm`'s output
is reference-only in the first place). This is a large, real software
mixer, not a stub. Confident findings:

- **Outer skeleton, argument-literal so essentially PROVEN**: at entry,
  calls IWRAM address `0x03000AFC` as a function, args `(0x03001144,
  count)` -- a "clear/reset the mix accumulator" pass. Then scans the
  32-channel array (`0x2C`/44-byte stride, base EWRAM `0x020008B4`, status
  byte at `+2`, `1` = active -- as already noted above) accumulating each
  active channel. After the scan, calls IWRAM address `0x03000B38` as a
  function, args `(0x03001144, savedArg0, savedArg1, count)` -- a
  "finalize/convert the accumulator to output" pass. `0x03001144` is never
  called, only ever passed as a pointer -- almost certainly the mix
  accumulator buffer address, read/written by both bookend calls. This
  upgrades all five of the previously-UNCONFIRMED IWRAM addresses from the
  pointer-table section above to PROVEN: they're real, independently-called
  code/data, not table-only noise.
- **`0x03000B30`/`0x03000B34`** are plain IWRAM *data* words (not
  functions): read, incremented by per-channel byte fields `+0x1E`/`+0x1F`
  (candidate: a running L/R output-level or position accumulator), and
  written back every active-channel iteration.
- **The `0x08FA9568` table is word-indexed, not struct-indexed as first
  assumed**: `kramWorker_MixChannels` computes an index from
  `(u8)[ch+0x20] + (u8)[ch+0x21]` and reads `table[index]` with a plain
  `lsl #2` (4-byte stride), then `bx`es through the result. Both real index
  values observed so far land on slot 7 within an 8-word run -- i.e. this
  *is* consistent with the original "5 addresses + 2 reserved + 1
  `kramMixChannel` function pointer, per 32-byte bank" reading (see
  "Effect/mixer-descriptor table" above), just now confirmed to be
  reached via `[ch+0x20]` (bank base) + `[ch+0x21]` (slot, `7` = "the
  mixer function") rather than a fixed offset. Revises the earlier
  "buffer addresses per entry are otherwise unconfirmed" note -- the
  mechanism generating the index is now understood, even though what
  picks a *different* bank (there are only 2 known banks, both landing on
  the same function) is not.
- **Confirms `0x2C`-stride channel struct fields** beyond `+0x00`
  (mode: `0` selects a simpler "no resampling" copy path at `0x08FB1CBC`,
  nonzero the full resampling path) and `+0x02` (status):
  - `+0x03`: loop-mode byte (`0`/`2` branches seen; forward vs. some kind
    of wrap/ping-pong handling)
  - `+0x08`, `+0x0C`: a position/limit `u32` pair, compared each step for
    loop-boundary wraparound
  - `+0x10`: a further length/start-offset `u32`
  - `+0x14`: signed `u32`, fixed-point (16.16) pitch/step -- `asr #16`
    taken as the per-step integer position delta
  - `+0x1C`: `u16`, another step-sized value (`lsr #2`'d before use)
  - `+0x1E`, `+0x1F`: bytes added into the `0x03000B30`/`0x03000B34`
    accumulators (see above)
  - `+0x20`, `+0x21`: bytes summed to index the `0x08FA9568` table (see
    above)
  These are a **different struct** from the effect-handler one documented
  in "`KramChannel` field offsets" above (that one's fields run to
  `+0x5D`, this one is only 44/`0x2C` bytes total) -- confirms the earlier
  "two different structs, not one" conclusion from a second, independent
  direction.
- **Uses the GBA BIOS division SWI (`swi 0x06`, `Div`) directly**, twice
  (mirrored in both the forward and the `0x08FB1C50` alternate branch), for
  position/step math -- notable since it's a different division path than
  the compiled `__rt_sdiv`-family routines documented in `docs/compiler.md`;
  the hot mixer path apparently prefers the BIOS call over the linked-in
  compiler runtime.

Net effect on the earlier open question ("worth checking the EWRAM/IWRAM
copy step"): there's now a third confirmed IWRAM code address
(`0x03000AFC`, `0x03000B38`, alongside the earlier `0x03000AB4`) whose
bytes have to come from *somewhere* in ROM given "No bulk startup copy
into IWRAM/EWRAM" above already ruled out a global copy -- finding that
local Krawall-specific copy (or confirming these are just linked directly
to run from IWRAM, e.g. via a linker script section this project hasn't
found the ROM-side evidence for yet) is the concrete next step on this
thread.

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
  originally flagged UNCONFIRMED (no reference outside this one table). Now
  **PROVEN**, superseding that: `kramWorker_MixChannels` itself (see the
  full writeup below) reads this same literal pool a second time and uses
  all five directly — no longer table-only.

## No bulk startup copy into IWRAM/EWRAM [PROVEN]

Traced execution from `EntryPoint` (`0x08000000`) to answer the open
question above about an EWRAM/IWRAM copy step: there isn't one. `EntryPoint`
sets up the IRQ/System stacks and the user IRQ vector (`0x03007FFC`), then
`sub_080000EC` does a single `bx` straight into `0x08029690`, which itself
just calls ~30 subsystem-`Init`-style functions back to back — no
scatter-load table walk (the classic ADS/RVCT `__main`/`Region$$Table`
pattern) appears anywhere between reset and there. So whatever put code at
`0x03000AB4` did it locally (Krawall's own init), not as part of a global
runtime-init step; there's nothing broader to find here.

## `kramMixChannel` — the per-channel resample/mix routine [STRUCTURAL MATCH]

`0x080471FC` (ARM, now seeded in `functions.us.cfg` as `kramMixChannel`) is
a 4x-unrolled fixed-point resampling loop, matching a classic software
audio channel mixer: a fractional sample-position accumulator at struct
offsets `+0x28`/`+0x2A`, per-channel volume bytes at `+0x1E`/`+0x1F`, and a
`mul`+`asr #3` volume-scale-and-accumulate into the output buffer (`ldrh
[lr]` / `strh [lr]`). Its remainder/tail case (`< 4` samples left) falls
through to `ldr ip, =0x03000AB4; bx ip` — this is the concrete call site
for the previously-flagged IWRAM address, and it's a real, hot, per-channel
path (matches `kramWorker_MixChannels`' 32-channel scan interpretation).
The IWRAM target itself is still not disassembled/named.

## Effect/mixer-descriptor table at `0x08FA9568` [STRUCTURAL MATCH]

Immediately after the Krawall `$Id` string block sits a two-part table,
read directly (not via gbadisasm, which can't reach function-pointer-only
targets):

1. **Two 32-byte "mixer descriptor" entries** (`0x08FA9568`–`0x08FA95A7`):
   each holds 5 IWRAM buffer addresses, 2 reserved/zero words, and a
   function pointer — both entries point to `kramMixChannel` above. Two
   entries lines up with the GBA's two hardware DirectSound FIFOs (A/B), or
   a ping-pong buffer pair; the 5 buffer addresses per entry are otherwise
   unconfirmed.
2. **A Krawall XM effect-command dispatch table**, starting at `0x08FA95B4`:
   repeating 12-byte entries of `{tick_fn, init_fn, flags}`. At least 40
   populated entries confirmed by direct reads (some `tick`-only, some with
   both `tick` and `init` set, `flags` observed as 0 or 1), consistent with
   one entry per XM effect letter (`0`–`9`, `A`–`Z`, plus volume-column
   effects). The table's exact full extent (there's more populated data
   past `0x08FA97F0`) hasn't been walked to a confirmed terminator yet.

   All table entries store the function pointer with the Thumb bit set
   (odd address, BX-style) — the real function start is `addr & ~1`. (Caught
   this by hand before it corrupted `functions.us.cfg`: gbadisasm silently
   errors with "function at 0x08048401 is not aligned" rather than
   crashing, so it's an easy mistake to catch, but seeding the raw odd
   address first triggered an unrelated-looking `Assertion 'tmp_cnt == 1'
   failed` abort — the alignment check apparently isn't hit until *after*
   some duplicate-registration bookkeeping, so the wrong crash message
   shows up first when other seeds nearby are also present.)

   Spot-checked 3 of the 41 handler addresses by direct disassembly
   (`0x08048400`, `0x08048578`, `0x08049424`) — all are real Thumb function
   starts (`push {..,lr}` / `pop {..}` / `bx`) that read/write byte and
   halfword fields of what's presumably a `KramChannel` struct. All 41 are
   now identified by name, and the struct fields fleshed out much further
   -- see "Naming the 41 effect handlers" and "`KramChannel` field offsets"
   below.

   All 41 addresses (`&~1`'d) are now seeded in `functions.us.cfg` as
   `thumb_func`, plus `kramMixChannel` above as `arm_func`; `just disasm us`
   and `just compare us` both still pass after adding them.

## Naming the 41 effect handlers, via `player.c`'s `effects[]`/`effectsVC[]` [STRUCTURAL MATCH, very high confidence]

The public Krawall repo (`github.com/sebknzl/krawall`, `lib/player.c`) defines
exactly this table shape:

```c
typedef void (*EffFunc)( MChannel*, bool );
typedef struct { EffFunc func1; EffFunc func2; u8 inbet1; } effectStruct;
static const effectStruct effects[] = { ... 50 entries ... };

typedef struct { EffFunc func; u8 inbet; } effectStructVC;
static const effectStructVC effectsVC[] = { ... 10 entries ... };
```

`{func1, func2, inbet1}` is exactly our `{tick_fn, init_fn, flags}` shape
(`func2`/`init_fn` only set for the 4 "dual" entries that combine a
volume-slide with vibrato or tone-porta). This is the same "API-shape
reference, not a byte-level source match" use of the public repo that
identified `kramWorker`'s naming conventions (see above) -- CLAUDE.md's
caution that the public repo is a different revision than what's compiled
into the ROM still applies; nothing here is a compiled-code diff.

**Verification**: extracted the `inbet`/`flags` bit for all 50 `effects[]`
slots (including the unused all-zero ones) directly from ROM and diffed
against the reference source's sequence -- **exact match, all 50 entries**,
including which specific unused-slot indices are zero. Stronger still: the
reference table reuses `eff_volslide_s3m` in slot 23 (paired with
`eff_vibrato`) and slot 24 (paired with `eff_portanote`), and reuses
`eff_volslide_xm` the same way in slots 49/50. In the ROM table, slots 23/24
literally point back at the *same* `tick_fn` address as slot 6
(`0x8048400`), with `init_fn` pointing at the same addresses as slots 20 and
19 respectively (`0x80497E0`, `0x8048A48`) -- and slots 49/50 do the
identical thing with slot 7's address (`0x8048578`) instead. That specific
reuse pattern reproducing exactly, across 4 independent slots, is not
something a coincidental table shape would produce. Also extracted and
verified all 10 `effectsVC[]` (volume-column) entries the same way -- exact
`inbet` match too, though those functions (`0x8049BAC`-`0x8049E14`) aren't
seeded in `functions.<ver>.cfg` yet since they weren't part of the original
41.

Effect-column table (`0x08FA95B4`-`0x08FA980C`, ref. `effects[1..50]`,
1-indexed to match the source comments -- index 0 and the three commented
`(!)`/`(*)` slots are unused/all-zero and not real functions):

| # | name (source) | `functions.us.cfg` name | tick addr | init addr |
|---|---|---|---|---|
| 1 | `eff_speed` | `kramEff_Speed` | `0x8049424` | |
| 2 | `eff_bpm` | `kramEff_Bpm` | `0x804943C` | |
| 3 | `eff_speedbpm` | `kramEff_SpeedBpm` | `0x804945C` | |
| 4 | `eff_patt_jump` | `kramEff_PattJump` | `0x8049A58` | |
| 5 | `eff_patt_break` | `kramEff_PattBreak` | `0x8049A64` | |
| 6 | `eff_volslide_s3m` | `kramEff_VolSlideS3M` | `0x8048400` | |
| 7 | `eff_volslide_xm` | `kramEff_VolSlideXM` | `0x8048578` | |
| 8 | `eff_volslide_df` | `kramEff_VolSlideDownFine` | `0x80494A0` | |
| 9 | `eff_volslide_uf` | `kramEff_VolSlideUpFine` | `0x80494F8` | |
| 10 | `eff_portadown_xm` | `kramEff_PortaDownXM` | `0x80496B8` | |
| 11 | `eff_portadown_s3m` | `kramEff_PortaDownS3M` | `0x8048998` | |
| 12 | `eff_portadown_f` | `kramEff_PortaDownFine` | `0x804971C` | |
| 13 | `eff_portadown_ef` | `kramEff_PortaDownExtraFine` | `0x8049780` | |
| 14 | `eff_portaup_xm` | `kramEff_PortaUpXM` | `0x80495DC` | |
| 15 | `eff_portaup_s3m` | `kramEff_PortaUpS3M` | `0x80488B4` | |
| 16 | `eff_portaup_f` | `kramEff_PortaUpFine` | `0x8049628` | |
| 17 | `eff_portaup_ef` | `kramEff_PortaUpExtraFine` | `0x8049670` | |
| 18 | `eff_volume` | `kramEff_Volume` | `0x8049B7C` | |
| 19 | `eff_portanote` | `kramEff_PortaNote` | `0x8048A48` | |
| 20 | `eff_vibrato` | `kramEff_Vibrato` | `0x80497E0` | |
| 21 | `eff_tremor` | `kramEff_Tremor` | `0x8048DC0` | |
| 22 | `eff_arpeggio` | `kramEff_Arpeggio` | `0x8048FD0` | |
| 23 | `eff_volslide_vibrato` | (reuses 6 + 20) | `0x8048400` | `0x80497E0` |
| 24 | `eff_volslide_porta` | (reuses 6 + 19) | `0x8048400` | `0x8048A48` |
| 25 | `eff_cvolume` | `kramEff_ChannelVolume` | `0x804959C` | |
| 26 | `eff_cvolslide` | `kramEff_ChannelVolSlide` | `0x80486E8` | |
| 27 | `eff_offset` | `kramEff_Offset` | `0x804989C` | |
| 28 | `eff_panslide` | `kramEff_PanSlide` | `0x8048784` | |
| 29 | `eff_retrig` | `kramEff_Retrig` | `0x8048E54` | |
| 30 | `eff_tremolo` | `kramEff_Tremolo` | `0x8048C60` | |
| 31 | `eff_fvibrato` | `kramEff_FineVibrato` | `0x8048B94` | |
| 32 | `eff_gvolume` | `kramEff_GlobalVolume` | `0x8049550` | |
| 33 | `eff_gvolslide` | `kramEff_GlobalVolSlide` | `0x8048630` | |
| 34 | `eff_pan` | `kramEff_Pan` | `0x8049A0C` | |
| 35 | `eff_panbrello` | `kramEff_PanBrello` | `0x8048D18` | |
| 36 | `eff_mark` | `kramEff_Mark` | `0x8049484` | |
| 37 | `eff_glissando` | `kramEff_Glissando` | `0x80498C8` | |
| 38 | `eff_wave_vibr` | `kramEff_WaveVibrato` | `0x80498E0` | |
| 39 | `eff_wave_trem` | `kramEff_WaveTremolo` | `0x8049944` | |
| 40 | `eff_wave_panb` | `kramEff_WavePanBrello` | `0x80499A8` | |
| 43 | `eff_patternloop` | `kramEff_PatternLoop` | `0x8049A7C` | |
| 44 | `eff_notecut` | `kramEff_NoteCut` | `0x8049AC4` | |
| 45 | `eff_notedelay` | `kramEff_NoteDelay` | `0x8049B00` | |
| 49 | `eff_volslide_vibrato_xm` | (reuses 7 + 20) | `0x8048578` | `0x80497E0` |
| 50 | `eff_volslide_porta_xm` | (reuses 7 + 19) | `0x8048578` | `0x8048A48` |

Volume-column table (`0x08FA980C`-`0x08FA985C`, ref. `effectsVC[1..10]`):

| # | name (source) | `functions.us.cfg` name | tick addr |
|---|---|---|---|
| 1 | `eff_VC_volslide_down` | `kramEff_VC_VolSlideDown` | `0x8049BAC` |
| 2 | `eff_VC_volslide_up` | `kramEff_VC_VolSlideUp` | `0x8049BFC` |
| 3 | `eff_VC_fvolslide_down` | `kramEff_VC_VolSlideDownFine` | `0x8049C50` |
| 4 | `eff_VC_fvolslide_up` | `kramEff_VC_VolSlideUpFine` | `0x8049C9C` |
| 5 | `eff_VC_vibrato_setspeed` | `kramEff_VC_VibratoSetSpeed` | `0x8049CE8` |
| 6 | `eff_VC_vibrato` | `kramEff_VC_Vibrato` | `0x80490CC` |
| 7 | `eff_VC_pan` | `kramEff_VC_Pan` | `0x8049D04` |
| 8 | `eff_VC_panslide_left` | `kramEff_VC_PanSlideLeft` | `0x8049D60` |
| 9 | `eff_VC_panslide_right` | `kramEff_VC_PanSlideRight` | `0x8049DB8` |
| 10 | `eff_VC_portanote` | `kramEff_VC_PortaNote` | `0x8049E14` |

All 51 functions (41 effect-column + 10 volume-column) are now named in
`functions.us.cfg`; `just check-all` still passes (renaming/seeding a
`functions.<ver>.cfg` entry can't change the produced bytes, but re-checked
anyway per hard rule 4).

`kramEff_VC_PortaNote`'s tick path (`0x08049E32`) is a direct `bl
kramEff_PortaNote` into the effect-column function above -- a real,
gbadisasm-verified symbolic cross-reference between the two tables, not
just matching shape. About as strong a confirmation of both names as is
possible without the original source.

## `KramChannel` field offsets, from reading all 51 handlers [STRUCTURAL MATCH]

Cross-referencing field accesses across all 51 named functions (effect +
volume-column) gives a much fuller picture than any single function did.
The recurring "recompute mix output" sequence --
`([ch+4] * [ch+5] * (s8)[ch+0x4D]) >> 12` passed to `sub_0804A2C8` -- alone
appears in over a dozen of them, which is what makes the following offsets
confident despite no single function proving all of them at once:

| offset | size | field | evidence |
|---|---|---|---|
| `+0x00` | 4 | sample/voice pointer | arg0 to `sub_0804A2C8` in every volume-affecting handler |
| `+0x04` | 1 | Volume (0-`0x40`) | set directly by `kramEff_Volume`, slid+clamped-at-`0x40` by all `VolSlide*`/`VC_VolSlide*` |
| `+0x05` | 1 | Channel Volume (0-`0x40`) | same shape, but set by `kramEff_ChannelVolume`/`ChannelVolSlide` instead -- confirms these are two distinct, both-multiplied-in volume factors, not the same field read two ways |
| `+0x06` | 1 (s8) | Panning (~-0x40..0x3F) | set/slid by `kramEff_VC_Pan`/`PanSlideLeft`/`PanSlideRight`, combined with a `+0x57` "pan envelope" offset before clamping |
| `+0x0C` | 2 | Period (live pitch) | read by vibrato as the base to offset from; written directly by the portamento family (`PortaUp*`/`PortaDown*`) |
| `+0x0E` | 2 | Period, post-vibrato | written only by `kramEff_VC_Vibrato`'s tick path (`period + waveTable[phase]*depth>>7`), consumed downstream (presumably by `kramMixChannel` or a callee) |
| `+0x18` | 1 | unclear | compared against small constants (`0x14`, `0x17`, `0x31`) in a handful of handlers; not yet pinned to a specific meaning |
| `+0x19` | 1 | current effect-column param (`xy`) | read generically as input by nearly all 41 effect-column handlers; several memoize a nonzero value into a handler-specific "remembered param" byte elsewhere in the struct (e.g. `+0x3C`, `+0x3E`, `+0x40`, `+0x44`) |
| `+0x1A` | 2 | tone-porta target delta | set by `kramEff_VC_PortaNote`'s init path from the low nibble of its param |
| `+0x20` | 1 | vibrato phase/position | incremented by `+0x21` (speed) each tick, `&0x3F`-wrapped, used ×2 as a halfword index into the `+0x24` waveform table |
| `+0x21` | 1 | vibrato speed | set by `kramEff_VC_VibratoSetSpeed` |
| `+0x22` | 1 | vibrato depth (×4 scaled) | set by `kramEff_VC_Vibrato`'s init path from the low nibble of its `+0x5D` param |
| `+0x24` | 4 | vibrato waveform table pointer | read by `kramEff_VC_Vibrato`, presumably set by `kramEff_WaveVibrato` (not yet checked) |
| `+0x48` | 1 | dirty/pending flag | read-and-cleared by several handlers when `+0x18 == 0x14`; likely tells the mixer a per-channel recompute is needed |
| `+0x4D` | 1 (s8) | volume-combine multiplier | third factor in the `([ch+4]*[ch+5]*[ch+0x4D])>>12` formula everywhere; not yet independently pinned to what sets it (candidate: baked-in panning contribution or instrument default volume) |
| `+0x57` | 1 | pan envelope offset | added to `+0x06` before the final pan clamp in `VC_Pan`/`PanSlideLeft`/`PanSlideRight` |
| `+0x5D` | 1 | current volume-column param | the volume-column equivalent of `+0x19` -- confirms the effect-column and volume-column params are stored as two separate bytes in the same struct, not shared |

**Global (not per-channel) fields, EWRAM `0x02001644`+**: `+0x1D`/`+0x1E`
hold Global Volume's value/raw-slide-param, written by
`kramEff_GlobalVolSlide` -- this is the player-wide state struct
(`docs/memory-map.md`'s earlier candidate `KramEngineState`), not
`KramChannel`.

**Resolving the earlier "two different offset pictures" question**: this
struct's fields run out to at least `+0x5D`, well past the 44-byte
(`0x2C`) stride `kramWorker_MixChannels` uses to scan its channel array
with a status byte at `+2`. Those two pictures don't reconcile into one
struct -- they're almost certainly **two different structs**: a compact,
hot-path mixer-channel struct (44 bytes, scanned every mix callback) and a
separate, larger per-track player/effect-state struct (this one, walked
once per tick by the effect handlers) that presumably holds a pointer into
the compact one. Revising the earlier "could be the same struct viewed
from a different base" note above -- it isn't.

## Searching for where IWRAM code gets installed — dead end, documented so it isn't re-walked

Follow-up to the confirmed-but-unexplained IWRAM code addresses above
(`0x03000AB4`, `0x03000AFC`, `0x03000B38`, and now several more — see
below). "No bulk startup copy into IWRAM/EWRAM" already ruled out a
global scatter-load; this was a search for a *local* Krawall-specific
copy. Static search only, no dynamic verification attempted this round.

**Expanded the known IWRAM code footprint.** Re-reading how the effect
handlers' "recompute mix output" call actually works revealed a
misreading from the earlier "Effect/mixer-descriptor table" section: the
literal addresses I'd read as a "table selector" argument to
`sub_0804A2C8` (`0x03000434`, `0x030004B4`, `0x030003E8`, `0x03000320`,
`0x03000090`, `0x03000BF0`, etc.) aren't data at all. `sub_0804A2C8` and
its neighbors (`sub_0804A2C0`..`sub_0804A2E4`, all defined right next to
each other at `0x0804A2C0`-`0x0804A2E4`) are **register-indirect call
trampolines** -- `sub_0804A2C8` is literally just `bx r2`, `sub_0804A2C4`
is `bx r1`, `sub_0804A2CC` is `bx r3`, etc. This is the standard
ARMv4T-Thumb interworking veneer pattern (Thumb has no `blx reg`, so
calling a function pointer held in a register other than what a direct
`bl` can reach needs a tiny glue stub). So each of those literals is
itself a real IWRAM function pointer, called through the trampoline --
meaning the actual IWRAM code footprint is considerably larger than the
5 addresses first flagged: at least `0x03000090`, `0x03000320`,
`0x030003E8`, `0x03000434`, `0x030004B4`, `0x03000578`, `0x03000AB4`,
`0x03000AFC`, `0x03000B38`, `0x03000BF0` are called as code (`0x03000B30`/
`0x03000B34` remain confirmed as plain data words, not code -- see the
`kramWorker_MixChannels` writeup above).

**Searched exhaustively for the copy mechanism, found none in the
Krawall-relevant code**:
- No `CpuSet`/`CpuFastSet` BIOS calls (`swi 0x0B`/`0x0C`) anywhere in the
  Krawall driver's code cluster (`0x08046000`-`0x08048000`) or near
  `kramWorker`/`kramWorker_MixChannels`.
- Fully read `kramWorker` itself (`0x08FB1E18`, the top-level per-callback
  entry point) -- no copy there either, just a buffer-space query (calls
  `0x08046E0C`, resolving the earlier-flagged "trace the query free space
  callback" next step -- it's exactly that, confirmed by this read) and a
  chunked loop calling `kramWorker_MixChannels`.
- Widened the literal-address scan to the whole ROM for anything writing
  `0x03000000`-`0x03002000`: found only individual small state-cell writes
  (bytes/halfwords) scattered across dozens of unrelated functions, never
  a bulk block copy.
- Found a real DMA3-register setup sequence (`sub_08049F0C`, a generic
  `DMA3Transfer(src, dest, count)` helper sitting right next to the effect
  tables) and chased it as the most promising lead yet -- **false alarm**.
  Its actual callers pass `0x0D000000` as the transfer address, which is
  the GBA's EEPROM save-data access range, not IWRAM; one caller
  (`sub_08049F8C`) does a write-then-read pair through that address, the
  standard GBA EEPROM read protocol. This is unrelated save-data I/O code
  that happens to sit near the Krawall tables in link order, not an IWRAM
  loader. Confirmed dead end, not worth re-checking.

**Conclusion**: the install mechanism for these ~10 IWRAM functions is
still unknown. Either it's a copy this search genuinely missed (candidates
not yet checked: the ~30 subsystem-init calls from `0x08029690` --
tracing which one is audio-specific was never done; or a copy that uses
plain `ldr`/`str` in a loop rather than any BIOS/DMA primitive, which a
literal-address search wouldn't catch if the loop computes the destination
arithmetically instead of loading it as one immediate), or these functions
are linked to run from IWRAM directly and something outside pure static
ROM analysis (an ELF section with separate LMA/VMA, or a linker-generated
region this project hasn't looked for yet) is responsible. The previous
"Dynamic verification attempt" below was inconclusive for a different
question (confirming `kramWorker` candidates) but never retried
specifically for this one (e.g. a hardware breakpoint on a write to
`0x03000090` would answer it directly) -- likely the fastest path forward
if this thread gets picked up again.

## Dynamic verification attempt — inconclusive, dropped for now

Tried to confirm the `kramWorker`/mixer candidates by attaching gdb to
mGBA's GDB stub (`--gdb`, port 2345) with the ROM running under a real BIOS
dump. Confirmed mGBA halts the CPU on `--gdb` until a client attaches
(observed BIOS boot sound only start after issuing `continue`), so the
mechanism works in principle. However, breakpoint+continue sequencing was
unreliable across many attempts — the stub would sometimes report a stop
snapshot on attach while simultaneously treating the target as "still
running" for subsequent commands, and reconnects would intermittently hang
with no response at all. Root cause not identified (possibly an mGBA
GDB-stub quirk/bug, possibly a client-side gdb version mismatch — not
determined). Dropped rather than continuing to iterate blindly; all
candidate identifications above remain at their stated confidence level
(STRUCTURAL MATCH / UNCONFIRMED), none upgraded to PROVEN by this attempt.
Worth revisiting later, possibly with an interactive (non-batch) gdb session
or a different debugging frontend.

## Next steps

- [ ] Do NOT expect the public Krawall repo to resolve function identity by
      diffing — it's a different source revision. Naming these functions
      will require either behavioral/structural inference from disassembly,
      or finding an actual 2003-era Krawall source snapshot if one exists
      (unlikely to be publicly available).
- [x] Trace the Thumb "query free space" callback at `0x08046E0C` -- it's
      called directly from `kramWorker` (see "Searching for where IWRAM
      code gets installed" below); not yet disassembled itself, just its
      call site and role confirmed.
- [x] Confirmed there's no global startup copy into IWRAM (see "No bulk
      startup copy" above) — dropped as a dead end. `0x03000AB4` is still
      un-disassembled; if it's installed at all rather than statically
      linked there, it must happen inside Krawall's own init path, not
      crt0. Worth revisiting only if a driver-local copy loop turns up.
- [x] Walked the effect-handler table at `0x08FA9568` to its confirmed end
      (`0x08FA985C`, right where the volume-column table `effectsVC[]`
      finishes) and named all 41 effect-column + 10 volume-column functions
      by matching the tables' `inbet`/`flags` sequences and dual-function
      reuse pattern against `player.c`'s `effects[]`/`effectsVC[]` -- see
      "Naming the 41 effect handlers" above, all seeded in
      `functions.us.cfg`.
- [x] Mapped many more `KramChannel` fields by cross-referencing all 51
      named handlers (see "`KramChannel` field offsets" above) and resolved
      the "two offset pictures" question: they're two different structs,
      not one -- `kramWorker_MixChannels`' 44-byte-stride array is a
      compact hot-path mixer-channel struct, separate from this larger
      per-track effect-state struct (fields run to at least `+0x5D`).
- [ ] Map more fields of the candidate `KramEngineState` (EWRAM
      `0x02001638`-`0x0200163E`); confirmed `+0x1D`/`+0x1E` there are
      Global Volume's value/raw-slide-param (via `kramEff_GlobalVolSlide`).
- [ ] Pin down what sets `KramChannel+0x4D` (the third factor in the
      volume-combine formula, candidate: baked-in panning or instrument
      default volume) and what `+0x18`/`+0x08` mean (compared against small
      constants like `0x14`/`0x17`/`0x31` in several handlers).
- [x] Found the 44-byte-stride compact mixer-channel struct's own fields by
      fully disassembling `kramWorker_MixChannels` with `objdump` (gbadisasm
      stops early on its mid-function indirect `bx`) -- see "Full
      disassembly of `kramWorker_MixChannels`" above. Also upgraded all 5
      previously-UNCONFIRMED IWRAM pointer-table addresses to PROVEN, and
      corrected the `0x08FA9568` table's indexing mechanism.
- [x] Searched for where the ~10 confirmed IWRAM code addresses
      (`0x03000090`, `0x03000320`, `0x030003E8`, `0x03000434`, `0x030004B4`,
      `0x03000578`, `0x03000AB4`, `0x03000AFC`, `0x03000B38`, `0x03000BF0`)
      get installed -- dead end for now, see "Searching for where IWRAM
      code gets installed" above. Ruled out `CpuSet`/`CpuFastSet` and a
      DMA-based copy (the one DMA setup found nearby turned out to be
      unrelated EEPROM save I/O). Fully read `kramWorker` itself, which
      also resolved the standalone "trace the query free space callback at
      `0x08046E0C`" item below -- it's exactly that, called from
      `kramWorker`. Next things to try if this gets picked up again: trace
      which of the ~30 subsystem-init calls from `0x08029690` is
      audio-specific, or go dynamic (hardware breakpoint on a write to
      `0x03000090`).
- [ ] Disassemble the ~10 IWRAM functions themselves (accumulator
      clear/finalize passes, the `kramMixChannel`-family functions reached
      through the `0x08FA9568` table, etc.) once their source bytes are
      located (can't `gbadisasm`/`objdump` a RAM address against the ROM
      file directly).
- [ ] Once functions are named (via inference, not source diff), begin
      populating `symbols.us.txt`. The 41 effect-handler names above are the
      first real candidates for this.
