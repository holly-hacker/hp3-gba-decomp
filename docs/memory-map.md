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
   halfword fields of what's presumably a `KramChannel` struct, at offsets
   `+0x08`, `+0x18`, `+0x19`, `+0x24`, `+0x3C`, `+0x48` (new candidate field
   offsets, not yet cross-checked against the `+0x2C`-stride/`+2`-status-byte
   picture from `kramWorker_MixChannels` above — could be the same struct
   viewed from a different base, needs reconciling before trusting either
   layout). All 41 are now identified by name -- see the next section.

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

Volume-column table (`0x08FA980C`-`0x08FA985C`, ref. `effectsVC[1..10]`) --
**not yet seeded in `functions.<ver>.cfg`**, addresses given for reference:

| # | name (source) | tick addr |
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

All 41 effect-column functions renamed in `functions.us.cfg` accordingly;
`just check-all` still passes (renaming a `functions.<ver>.cfg` seed can't
change the produced bytes, but re-checked anyway per hard rule 4).

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
- [ ] Trace the Thumb "query free space" callback at `0x08046E0C`.
- [x] Confirmed there's no global startup copy into IWRAM (see "No bulk
      startup copy" above) — dropped as a dead end. `0x03000AB4` is still
      un-disassembled; if it's installed at all rather than statically
      linked there, it must happen inside Krawall's own init path, not
      crt0. Worth revisiting only if a driver-local copy loop turns up.
- [ ] Map more fields of the candidate `KramEngineState` (EWRAM
      `0x02001638`-`0x0200163E`) and reconcile the two different
      `KramChannel` offset pictures now on file: 44-byte stride/status byte
      at `+2` (from `kramWorker_MixChannels`) vs. `+0x08`/`+0x18`/`+0x19`/
      `+0x24`/`+0x3C`/`+0x48` (from the effect-handler spot checks) — same
      struct from a different base, or two different structs.
- [x] Walked the effect-handler table at `0x08FA9568` to its confirmed end
      (`0x08FA985C`, right where the volume-column table `effectsVC[]`
      finishes) and named all 41 effect-column functions by matching the
      table's `inbet`/`flags` sequence and dual-function reuse pattern
      against `player.c`'s `effects[]`/`effectsVC[]` -- see "Naming the 41
      effect handlers" above. The 10 volume-column (`effectsVC[]`) handler
      addresses are identified but not yet seeded in `functions.<ver>.cfg`.
- [ ] Once functions are named (via inference, not source diff), begin
      populating `symbols.us.txt`. The 41 effect-handler names above are the
      first real candidates for this.
