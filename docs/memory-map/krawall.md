# Krawall audio engine — memory map

See [`../memory-map.md`](../memory-map.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the RNG
memory-map split out separately at [`rng.md`](rng.md).

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
  "diff against known source to skip decompiling" shortcut.

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

### Full disassembly of `mixReal`, and the 44-byte channel struct [PROVEN mechanics, STRUCTURAL MATCH interpretation]

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
  makes all five IWRAM addresses from the pointer-table section above
  PROVEN: they're real, independently-called code/data, not table-only
  noise.
- **`0x03000B30`/`0x03000B34`** are plain IWRAM *data* words (not
  functions): read, incremented by per-channel byte fields `+0x1E`/`+0x1F`
  (candidate: a running L/R output-level or position accumulator), and
  written back every active-channel iteration.
- **The `0x08FA9568` table is word-indexed, not struct-indexed**:
  `mixReal` computes an index from
  `(u8)[ch+0x20] + (u8)[ch+0x21]` and reads `table[index]` with a plain
  `lsl #2` (4-byte stride), then `bx`es through the result. Both real index
  values observed so far land on slot 7 within an 8-word run -- i.e. this
  *is* consistent with the "5 addresses + 2 reserved + 1
  `kramMixChannel` function pointer, per 32-byte bank" reading (see
  "Effect/mixer-descriptor table" above), reached via `[ch+0x20]` (bank
  base) + `[ch+0x21]` (slot, `7` = "the mixer function") rather than a
  fixed offset. What picks a *different* bank (there are only 2 known
  banks, both landing on the same function) is not understood.
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
  **PROVEN**, not table-only: `mixReal` itself (see the full writeup
  below) reads this same literal pool a second time and uses all five
  directly.

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
path (matches `mixReal`' 32-channel scan interpretation).
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
   halfword fields of what's presumably a `KramChannel` struct. All 41
   are identified by name -- see "Naming the 41 effect handlers" and
   "`KramChannel` field offsets" below.

   All 41 addresses (`&~1`'d) are seeded in `functions.us.cfg` as
   `thumb_func`, plus `kramMixChannel` above as `arm_func`; `just disasm us`
   and `just compare us` both pass with them.

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

| # | name | tick addr | init addr |
|---|---|---|---|
| 1 | `eff_speed` | `0x8049424` | |
| 2 | `eff_bpm` | `0x804943C` | |
| 3 | `eff_speedbpm` | `0x804945C` | |
| 4 | `eff_patt_jump` | `0x8049A58` | |
| 5 | `eff_patt_break` | `0x8049A64` | |
| 6 | `eff_volslide_s3m` | `0x8048400` | |
| 7 | `eff_volslide_xm` | `0x8048578` | |
| 8 | `eff_volslide_df` | `0x80494A0` | |
| 9 | `eff_volslide_uf` | `0x80494F8` | |
| 10 | `eff_portadown_xm` | `0x80496B8` | |
| 11 | `eff_portadown_s3m` | `0x8048998` | |
| 12 | `eff_portadown_f` | `0x804971C` | |
| 13 | `eff_portadown_ef` | `0x8049780` | |
| 14 | `eff_portaup_xm` | `0x80495DC` | |
| 15 | `eff_portaup_s3m` | `0x80488B4` | |
| 16 | `eff_portaup_f` | `0x8049628` | |
| 17 | `eff_portaup_ef` | `0x8049670` | |
| 18 | `eff_volume` | `0x8049B7C` | |
| 19 | `eff_portanote` | `0x8048A48` | |
| 20 | `eff_vibrato` | `0x80497E0` | |
| 21 | `eff_tremor` | `0x8048DC0` | |
| 22 | `eff_arpeggio` | `0x8048FD0` | |
| 23 | `eff_volslide_vibrato` (reuses 6 + 20) | `0x8048400` | `0x80497E0` |
| 24 | `eff_volslide_porta` (reuses 6 + 19) | `0x8048400` | `0x8048A48` |
| 25 | `eff_cvolume` | `0x804959C` | |
| 26 | `eff_cvolslide` | `0x80486E8` | |
| 27 | `eff_offset` | `0x804989C` | |
| 28 | `eff_panslide` | `0x8048784` | |
| 29 | `eff_retrig` | `0x8048E54` | |
| 30 | `eff_tremolo` | `0x8048C60` | |
| 31 | `eff_fvibrato` | `0x8048B94` | |
| 32 | `eff_gvolume` | `0x8049550` | |
| 33 | `eff_gvolslide` | `0x8048630` | |
| 34 | `eff_pan` | `0x8049A0C` | |
| 35 | `eff_panbrello` | `0x8048D18` | |
| 36 | `eff_mark` | `0x8049484` | |
| 37 | `eff_glissando` | `0x80498C8` | |
| 38 | `eff_wave_vibr` | `0x80498E0` | |
| 39 | `eff_wave_trem` | `0x8049944` | |
| 40 | `eff_wave_panb` | `0x80499A8` | |
| 43 | `eff_patternloop` | `0x8049A7C` | |
| 44 | `eff_notecut` | `0x8049AC4` | |
| 45 | `eff_notedelay` | `0x8049B00` | |
| 49 | `eff_volslide_vibrato_xm` (reuses 7 + 20) | `0x8048578` | `0x80497E0` |
| 50 | `eff_volslide_porta_xm` (reuses 7 + 19) | `0x8048578` | `0x8048A48` |

Volume-column table (`0x08FA980C`-`0x08FA985C`, ref. `effectsVC[1..10]`):

| # | name | tick addr |
|---|---|---|
| 1 | `eff_VC_volslide_down` | `0x8049BAC` |
| 2 | `eff_VC_volslide_up` | `0x8049BFC` |
| 3 | `eff_VC_fvolslide_down` | `0x8049C50` |
| 4 | `eff_VC_fvolslide_up` | `0x8049C9C` |
| 5 | `eff_VC_vibrato_setspeed` | `0x8049CE8` |
| 6 | `eff_VC_vibrato` | `0x80490CC` |
| 7 | `eff_VC_pan` | `0x8049D04` |
| 8 | `eff_VC_panslide_left` | `0x8049D60` |
| 9 | `eff_VC_panslide_right` | `0x8049DB8` |
| 10 | `eff_VC_portanote` | `0x8049E14` |

All 51 functions (41 effect-column + 10 volume-column) are now named in
`functions.us.cfg`; `just check-all` still passes (renaming/seeding a
`functions.<ver>.cfg` entry can't change the produced bytes, but re-checked
anyway per hard rule 4).

`eff_VC_portanote`'s tick path (`0x08049E32`) is a direct `bl
eff_portanote` into the effect-column function above -- a real,
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
| `+0x04` | 1 | Volume (0-`0x40`) | set directly by `eff_volume`, slid+clamped-at-`0x40` by all `VolSlide*`/`VC_VolSlide*` |
| `+0x05` | 1 | Channel Volume (0-`0x40`) | same shape, but set by `eff_cvolume`/`ChannelVolSlide` instead -- confirms these are two distinct, both-multiplied-in volume factors, not the same field read two ways |
| `+0x06` | 1 (s8) | Panning (~-0x40..0x3F) | set/slid by `eff_VC_pan`/`PanSlideLeft`/`PanSlideRight`, combined with a `+0x57` "pan envelope" offset before clamping |
| `+0x0C` | 2 | Period (live pitch) | read by vibrato as the base to offset from; written directly by the portamento family (`PortaUp*`/`PortaDown*`) |
| `+0x0E` | 2 | Period, post-vibrato | written only by `eff_VC_vibrato`'s tick path (`period + waveTable[phase]*depth>>7`), consumed downstream (presumably by `kramMixChannel` or a callee) |
| `+0x18` | 1 | unclear | compared against small constants (`0x14`, `0x17`, `0x31`) in a handful of handlers; not yet pinned to a specific meaning |
| `+0x19` | 1 | current effect-column param (`xy`) | read generically as input by nearly all 41 effect-column handlers; several memoize a nonzero value into a handler-specific "remembered param" byte elsewhere in the struct (e.g. `+0x3C`, `+0x3E`, `+0x40`, `+0x44`) |
| `+0x1A` | 2 | tone-porta target delta | set by `eff_VC_portanote`'s init path from the low nibble of its param |
| `+0x20` | 1 | vibrato phase/position | incremented by `+0x21` (speed) each tick, `&0x3F`-wrapped, used ×2 as a halfword index into the `+0x24` waveform table |
| `+0x21` | 1 | vibrato speed | set by `eff_VC_vibrato_setspeed` |
| `+0x22` | 1 | vibrato depth (×4 scaled) | set by `eff_VC_vibrato`'s init path from the low nibble of its `+0x5D` param |
| `+0x24` | 4 | vibrato waveform table pointer | read by `eff_VC_vibrato`, presumably set by `eff_wave_vibr` (not yet checked) |
| `+0x48` | 1 | dirty/pending flag | read-and-cleared by several handlers when `+0x18 == 0x14`; likely tells the mixer a per-channel recompute is needed |
| `+0x4D` | 1 (s8) | volume-combine multiplier | third factor in the `([ch+4]*[ch+5]*[ch+0x4D])>>12` formula everywhere; not yet independently pinned to what sets it (candidate: baked-in panning contribution or instrument default volume) |
| `+0x57` | 1 | pan envelope offset | added to `+0x06` before the final pan clamp in `VC_Pan`/`PanSlideLeft`/`PanSlideRight` |
| `+0x5D` | 1 | current volume-column param | the volume-column equivalent of `+0x19` -- confirms the effect-column and volume-column params are stored as two separate bytes in the same struct, not shared |

**Global (not per-channel) fields, EWRAM `0x02001644`+**: `+0x1D`/`+0x1E`
hold Global Volume's value/raw-slide-param, written by
`eff_gvolslide` -- this is the player-wide state struct
(this document's earlier candidate `KramEngineState`), not
`KramChannel`.

**Resolving the earlier "two different offset pictures" question**: this
struct's fields run out to at least `+0x5D`, well past the 44-byte
(`0x2C`) stride `mixReal` uses to scan its channel array
with a status byte at `+2`. Those two pictures don't reconcile into one
struct -- they're almost certainly **two different structs**: a compact,
hot-path mixer-channel struct (44 bytes, scanned every mix callback) and a
separate, larger per-track player/effect-state struct (this one, walked
once per tick by the effect handlers) that presumably holds a pointer into
the compact one. Revising the earlier "could be the same struct viewed
from a different base" note above -- it isn't.

## Where IWRAM code gets installed — SOLVED [PROVEN]

Resolved via mGBA's built-in debugger console (not the gdb remote stub --
that had reliability problems before, see "Dynamic verification attempt"
below; mGBA's native `watch`/`continue` commands worked cleanly). Set a
write watchpoint on `0x03000090` (one of the confirmed IWRAM code
addresses) from a cold reset and `continue`d past one false hit (the BIOS
itself zero-clears IWRAM early in boot, before any game code runs -- PC
still inside the BIOS ROM, `0x000003xx`, at that point). The second hit
landed at PC `0x0802C4FC`, deep in game code, mid-loop, with register
state pointing at a plain word-copy loop (`ldmia`/`stmia` + tail byte
copy) -- i.e. a compiled `memcpy`. Register values at the trap
(`r4`/length, `r5`-`r6`/src, `r7`/dest, `lr`/caller) plus reading the
caller statically nail down the whole picture:

- **`0x0802C4BC`** is a general-purpose compiled `memcpy(dest, src, len)`
  -- standard word-copy-with-alignment-check shape, confirmed independently
  by a Ghidra decompilation of the same address matching byte-for-byte in
  structure (unaligned fallback + word loop + tail bytes). Named `memcpy`
  in `functions.us.cfg`.
- **`0x0803FDB0`** is the actual installer, called once from the game's
  top-level init sequence at `0x08029690` (`bl 0x0803FDB0` at `0x08029734`
  -- this is the same init-call chain traced all the way back in "No bulk
  startup copy into IWRAM/EWRAM" above; it was never itself a
  `gbadisasm` seed, and its target `0x08029690` is reached from
  `EntryPoint` only via an indirect `bx`, which is exactly why
  `gbadisasm`'s direct-branch-only spidering never reached any of this
  code on its own). Named `kramInstall` in `functions.us.cfg`. It does
  two back-to-back `memcpy` calls, source/dest/length all literal:
  - `memcpy(dest=0x03000000, src=0x08FB0DB0, len=0x1598)` -- the IWRAM
    install. `0x1598` = 5528 bytes, comfortably covering every IWRAM
    address flagged throughout this document (`0x03000090` through
    `0x03001144`+).
  - `memcpy(dest=0x02000000, src=0x08FB2348, len=0x27F8)` -- and
    immediately after, an **EWRAM install**.
    `0x08FB2348` is exactly where the first copy's source region ends
    (`0x08FB0DB0 + 0x1598`), so the ROM stores one contiguous
    `0x3D90`-byte image at `0x08FB0DB0`-`0x08FB4B40` that gets split
    across both copies. `0x02000000` (EWRAM base) is very likely where
    `KramEngineState` and the `0x020008B4` channel-array base actually
    live -- these are inside a *copied* image, not simple linked EWRAM
    globals. Every EWRAM address referenced throughout this document
    should be checked for whether it falls in
    `0x02000000`-`0x02002800`.
  - Both length constants are stored in ROM as full addresses
    (`0x03001598`, `0x020027F8` respectively) and masked with `0xFFFFFF`
    at the call site rather than stored as plain lengths -- reads like
    linker-generated region-end symbols (`__iwram_end`, `__ewram_end`)
    rather than hand-written constants, though not confirmed.
  - Also writes byte `8` to IWRAM `0x03005AC0` just before the copies --
    candidate "driver state" flag, not investigated further.

This also answers "verify whether `0x03000AB4`/`kramMixChannel`'s tail
target etc. are installed rather than statically linked" from multiple
sections above: they're installed, via this one `kramInstall` call, not
per-function.

### How this was tracked down: static search first, then dynamic

"No bulk startup copy into IWRAM/EWRAM" (above) already ruled out a
global scatter-load, so this was a search for a *local* Krawall-specific
copy. The static-only pass below didn't find it -- what finally worked was
going dynamic (see the resolution above): a single write watchpoint in
mGBA's own debugger console, not the gdb remote stub (unreliable here,
see "Dynamic verification attempt" below). Recorded for anyone
re-deriving this:

**The IWRAM code footprint is larger than a literal-scan suggests.** In
the effect handlers' "recompute mix output" call, the literal addresses
passed to `sub_0804A2C8` (`0x03000434`, `0x030004B4`, `0x030003E8`,
`0x03000320`, `0x03000090`, `0x03000BF0`, etc.) are not a "table
selector" argument, and not data at all. `sub_0804A2C8` and
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
`mixReal` writeup above).

**Searched exhaustively for the copy mechanism, found none in the
Krawall-relevant code**:
- No `CpuSet`/`CpuFastSet` BIOS calls (`swi 0x0B`/`0x0C`) anywhere in the
  Krawall driver's code cluster (`0x08046000`-`0x08048000`) or near
  `kramWorker`/`mixReal`.
- Fully read `kramWorker` itself (`0x08FB1E18`, the top-level per-callback
  entry point) -- no copy there either, just a buffer-space query (calls
  `0x08046E0C`, resolving the earlier-flagged "trace the query free space
  callback" next step -- it's exactly that, confirmed by this read) and a
  chunked loop calling `mixReal`.
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

A static search alone will not reach `kramInstall`: it is called only
through the same indirect-`bx` chain (`EntryPoint` -> `0x08029690`) that
"No bulk startup copy" flags as invisible to `gbadisasm`'s
direct-branch-only spidering, so literal-address scans over
already-disassembled territory never see it. Either walk all ~30 calls
from `0x08029690` by hand, or go straight to a watchpoint -- dynamic
verification answers it in two hits.

## Cross-referencing everything above against the public Krawall source [STRUCTURAL MATCH, unusually strong]

CLAUDE.md's standing caution applies as always: the public repo
(`github.com/sebknzl/krawall`) is a different source revision than what's
compiled into this ROM (no `$Id` tags, git history starts 2013), so
nothing here is a byte-level match -- but as an API-shape/naming
reference it confirms nearly everything mapped in this document by
inference, field for field. Compared against `lib/mixer.c`,
`lib/mixer.h`, `lib/mixer_private.h`, `lib/mixer.arm.c`,
`lib/mixer_private.arm.c`, `lib/directsound.c`, `lib/general.c`,
`lib/types.h`.

**`struct MixChannel` (`mixer_private.h`) matches the 44-byte channel
struct almost field-for-field.** Computing byte offsets from the C
struct (natural ARM alignment, `chandle` is a 4-byte union):

| field | computed offset | our finding | match |
|---|---|---|---|
| `vol` (u8) | `+0x00` | -- | (not independently confirmed, but consistent with position) |
| `pan` (s8) | `+0x01` | -- | consistent with `KramChannel`-the-other-struct's `+0x06`? No -- see caveat below |
| `status` (u8) | `+0x02` | status byte, `1`=active | **exact** |
| `loop` (u8) | `+0x03` | loop-mode byte, `0`/`2` seen | **exact** -- source's `LOOP_NORMAL=1`/`LOOP_BIDIR=2` explains the `2` we saw |
| `start`/`pos`/`end` (ptr×3) | `+0x04`/`+0x08`/`+0x0C` | position/limit `u32` pair at `+0x08`/`+0x0C` | **exact** (we just hadn't separately identified `start`) |
| `loopLength` (u32) | `+0x10` | further length/start field at `+0x10` | **exact** |
| `inc` (s32) | `+0x14` | signed fixed-point pitch/step at `+0x14` | **exact** |
| `id` (chandle, u32) | `+0x18` | -- | not independently identified |
| `frac` (u16) | `+0x1C` | -- | plausible match for our `+0x1C` "step-sized u16" note, though that was tentative |
| `lvol`/`rvol` (u8×2) | `+0x1E`/`+0x1F` | bytes summed into the `0x03000B30`/`0x03000B34` output accumulators | **very likely match** -- left/right volume being accumulated into stereo output sums is exactly what those two IWRAM words are for |
| `hq`/`mixFunc`/`hqs` (u8×3) | `+0x20`/`+0x21`/`+0x22` | bytes summed to index the `0x08FA9568` table at `+0x20`/`+0x21` | **very likely match, refines earlier read** -- see below |

Computed struct size from the public source is `0x28` (40) bytes; our
observed stride is `0x2C` (44) -- a 4-byte discrepancy, likely
compiler-specific padding (this ROM is armcc/RVCT-compiled, the public
source targets GCC/devkitARM -- see `docs/compiler.md`) or a genuine
extra field in whatever revision shipped in this game. Not resolved this
pass.

**Refines the `0x08FA9568` table read**: `mixer.arm.c` defines
`mixPanTable[]`, a **16-entry** function-pointer array (`mixLeft`,
`mixLeftHQ`, `mixRight`, `mixRightHQ`, `mixCenter`, `mixCenterHQ`,
`mixStereo`, `mixStereoHQ`, plus HQ-doubled again for a ramp-out
variant), indexed by `chn->hq | chn->mixFunc` (`SETQUALITY` sets `hq` to
`0` or `8`, i.e. a bit-3 flag, `SETPANNING` sets `mixFunc` to `0`-`7`) --
this is *exactly* the `[ch+0x20] + [ch+0x21]`-computed index into
`0x08FA9568` documented above, and identifies it as "HQ flag `×8` +
pan-mode `0`-`7`" rather than an opaque "bank + slot" pair. That makes
the "5 addresses + 2 reserved + 1 function pointer per 32-byte bank"
reading of that table likely wrong in detail (probably misattributing
neighboring data as part of the table) -- **worth a re-look**, with a
concrete 16-entry, 4-byte-stride shape to check
against, and 8 real names (`mixLeft`/`mixLeftHQ`/etc.) to try to assign
if the ROM populates more than the 2 slots found so far. Since this game
apparently ships built for stereo-only DirectSound output (see
`dsInit`/`dsStereo` below), it'd make sense if only the `mixStereo`/
`mixStereoHQ` slots are populated and the rest are zero -- consistent
with what was actually seen.

**`mixReal` matches `mixer_private.arm.c`'s `mixReal()`
almost line for line**: clears the accumulator (`mixClear(mixBuffer,
amount)` -- our `0x03000AFC` call), then `for(i=CHANNELNUM;i;i--,c++) if
(c->status != CHN_ACTIVE) continue;` (our 32-channel/`+2`-status loop,
`CHANNELNUM` confirmed `#define`d to exactly `32`), and its `DOLOOP`
macro (`LOOP_BIDIR`: negate `c->inc`; else: `c->pos -= c->loopLength`)
matches our "position/limit pair + signed pitch/step, direction via
sign" read of the mixer loop precisely.

**`channels[CHANNELNUM]` (the 44-byte-struct array itself) is declared
`IWRAM`, or `EWRAM` if built with `IWRAM_USAGE_SMALL`** (`mixer.c`).
This ROM's array lives at EWRAM `0x020008B4` (documented since the very
first pass through this driver) -- meaning **this game was built with
the small/reduced IWRAM-usage config**, not Krawall's default.

**`getDmaAddress(left, right)` (`directsound.c`) is an exact behavioral
match for the "query free space" callback at `0x08046E0C`**, called
directly from `kramWorker`: same signature (returns available sample
count, writes two output buffer pointers), same "only refill the DMA
half that isn't currently playing" logic (`dmaBlock == currMixBlock>>1`
check). Named `getDmaAddress` in `functions.us.cfg` (`ds` = the
public source's own `directsound.c` naming prefix). Its own two DMA
channels (`DM1`/`DM2`, one per stereo side, each with its own
`lBuffer`/`rBuffer`) is the real-source explanation for the "two banks"
in the `0x08FA9568` table -- an L/R DirectSound FIFO, not a generic
mode-select mechanism.

**`kragInit()` (`general.c`, the public source's top-level init) shows
no explicit IWRAM copy** -- consistent with the hypothesis that
`kramInstall`'s explicit `memcpy`-based install (found above) is
specific to *this* armcc/RVCT-compiled build. The public source relies on
GCC/devkitARM's `IWRAM`/`IWRAM_CODE` section attributes plus
devkitARM's crt0 auto-copying `.iwram`-attributed data at startup; ADS/
RVCT has no equivalent crt0 behavior linked into this ROM (confirmed
separately in "No bulk startup copy into IWRAM/EWRAM" above), so
whoever ported Krawall for this game's toolchain apparently added an
explicit install call to compensate. Plausible explanation, not proven.

Also noted in passing, not investigated: `directsound.c` calls
`kradInterruptUndoCodeMod()` on deinit, implying the interrupt handler
uses **self-modifying code** -- a real technique worth knowing about if
`0x08046E0C`'s neighborhood or the interrupt vector code ever gets
walked, but out of scope here.

## Dynamic verification attempt (gdb stub) — inconclusive, dropped

Use mGBA's own built-in debugger console for dynamic verification, not
the gdb remote stub described in this section -- see "Where IWRAM code
gets installed" above, where a `watch`/`continue` pair resolved the
question in two hits. This section is kept because the gdb-stub problem
itself was never diagnosed and could resurface if that path is tried
again.

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

- [ ] New lead from `battle.md`: `ShowBattleMessage`'s `SpellLevelUp` case
      calls `PlaySoundEffect_candidate` (`0x0803FF70`), which forwards into
      `0x08047DFC` -- a function inside this driver's cluster that
      manipulates a full per-channel state array, looking closer to a
      module-switch (`kramPlayModule`-equivalent) than a one-shot SFX
      trigger. Not traced further from this doc's side yet.
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
      not one -- `mixReal`' 44-byte-stride array is a
      compact hot-path mixer-channel struct, separate from this larger
      per-track effect-state struct (fields run to at least `+0x5D`).
- [ ] Map more fields of the candidate `KramEngineState` (EWRAM
      `0x02001638`-`0x0200163E`); confirmed `+0x1D`/`+0x1E` there are
      Global Volume's value/raw-slide-param (via `eff_gvolslide`).
- [ ] Pin down what sets `KramChannel+0x4D` (the third factor in the
      volume-combine formula, candidate: baked-in panning or instrument
      default volume) and what `+0x18`/`+0x08` mean (compared against small
      constants like `0x14`/`0x17`/`0x31` in several handlers).
- [x] Found the 44-byte-stride compact mixer-channel struct's own fields by
      fully disassembling `mixReal` with `objdump` (gbadisasm
      stops early on its mid-function indirect `bx`) -- see "Full
      disassembly of `mixReal`" above, which also establishes all 5 IWRAM
      pointer-table addresses as PROVEN and pins down the `0x08FA9568`
      table's indexing mechanism.
- [x] Found where the ~10 confirmed IWRAM code addresses get installed --
      **solved**, see "Where IWRAM code gets installed" above. Live write
      watchpoint (mGBA's own debugger console, not the gdb stub) on
      `0x03000090` from cold reset caught the exact `memcpy` call:
      `kramInstall` (`0x0803FDB0`) does two back-to-back `memcpy`s from one
      contiguous ROM image at `0x08FB0DB0`-`0x08FB4B40` -- one to IWRAM
      `0x03000000` (`0x1598` bytes), one to EWRAM `0x02000000` (`0x27F8`
      bytes). Both named in `functions.us.cfg`.
- [ ] Check whether `KramEngineState` (`0x02001638`+) and the
      `0x020008B4` channel-array base actually fall inside the EWRAM
      install range (`0x02000000`-`0x02002800`) -- if so, they're
      copied-image contents, not independently-linked globals, which may
      change how confidently their exact addresses can be trusted across
      a JP-vs-US comparison (worth checking whether `functions.jp.cfg`'s
      equivalent copy uses the same addresses).
- [ ] Disassemble the ~10 IWRAM functions themselves (accumulator
      clear/finalize passes, the `kramMixChannel`-family functions reached
      through the `0x08FA9568` table, etc.) -- now unblocked, since the
      source bytes are known to live at `0x08FB0DB0`+ in ROM (offset by
      `installed_addr - 0x03000000` for IWRAM ones, `installed_addr -
      0x02000000 + 0x1598` for EWRAM ones).
- [x] Cross-referenced the whole session's findings against the public
      Krawall source (`mixer.c`/`mixer.h`/`mixer_private.h`/`mixer.arm.c`/
      `mixer_private.arm.c`/`directsound.c`/`general.c`) -- see
      "Cross-referencing everything above against the public Krawall
      source" above. Confirmed `struct MixChannel` field-for-field
      (`status`@`+2`, `loop`@`+3`, `inc`@`+0x14` exact), named
      `getDmaAddress` (`0x08046E0C`), found this ROM was built with
      Krawall's `IWRAM_USAGE_SMALL` config (channel array in EWRAM, not
      IWRAM -- new finding), and refined (not yet finished) the
      `0x08FA9568` table read via `mixPanTable[]`'s 16-entry shape.
- [ ] Re-derive the `0x08FA9568` table's real shape now that
      `mixPanTable[]` gives a concrete 16-entry, 4-byte-stride model
      (indexed by `hq<<3 | mixFunc`) to check against, instead of the
      probably-wrong "32-byte descriptor bank" reading from earlier in
      this document.
- [ ] Resolve the 4-byte size discrepancy between the public source's
      computed `MixChannel` size (`0x28`) and this ROM's observed stride
      (`0x2C`) -- compiler padding difference or a real extra field.
- [ ] Once functions are named (via inference, not source diff), begin
      populating `symbols.us.txt`. The 41 effect-handler names above are the
      first real candidates for this.
