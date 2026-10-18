# Krawall audio engine — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED). The module, pattern and sample
formats are in [`../formats/krawall.md`](../formats/krawall.md).

## Identity [PROVEN]

The game's audio driver is Krawall, Sebastian Kienzl's XM/S3M player,
licensed LGPL-2.1-or-later. Both ROMs carry its CVS keyword string
`$Id: Krawall $Date: 2003/09/01 06:51:01 $` (US `0x08FA953C`, JP
`0x08F3C9CC`), and the library is the same in both versions apart from
relocated addresses.

The source lives in `3rd_party/krawall/`, with its headers in
`include/3rd_party/krawall/`. It starts from the public repository
(<https://github.com/sebknzl/krawall>, commit `9a2b869`, 2013) and is
edited only where the 2003 revision in the ROM differs. Each change is
marked with an `// HP3-GBA:` comment; `mixer_func.S`, `player_tables.c`
and `player_tables.h` are upstream's unchanged. Compiled unchanged, the
public source already reproduces twenty functions byte for byte. Krawall is compiled with GCC 3.0.2 at
`-O3` (see [`../compiler.md`](../compiler.md)) and configured with
`IWRAM_USAGE_SMALL` at the default 16 kHz, 60 Hz: the mixing buffers,
channels and player state live in EWRAM.

## Link layout [PROVEN for matched objects, STRUCTURAL MATCH otherwise]

The objects are linked in the order `general`, `directsound`,
`directsound_asm`, `mixer`, `mixer.arm`, `mixer_func`,
`mixer_private.arm`, `player`, `player_tables`, `stub`. Each section type
is gathered in that order:

| Section | US ROM | JP ROM | Runs at |
|---|---|---|---|
| `.text` | `0x08046D0C`-`0x08049E84` | `0x08046C38`-`0x08049DB0` | ROM |
| `.rodata` | `0x08FA953C`-`0x08FAA7CC` | `0x08F3C9CC`-`0x08F3DC5C` | ROM |
| `.iwram` | `0x08FB0DB0`-`0x08FB2348` | `0x08F44240`-`0x08F457D8` | `0x03000000`-`0x03001598` |
| `.ewram` | `0x08FB2348`-`0x08FB4B40` | `0x08F457D8`-`0x08F47FD0` | `0x02000000`-`0x020027F8` |

`kramInstall` copies both RAM images at boot, through `CopyMemory`, before
`InitAudio` calls `kragInit`. Uninitialised `.iwram`/`.ewram` variables are
stored as zeros in the images. `g_pKrawallIwramStart` and its neighbours
hold the same bounds for `ClearWorkRam`, which zeroes the RAM above both
images.

### `.text` (US)

| Object | Range | Functions |
|---|---|---|
| `general.c` | `0x08046D0C`-`0x08046D2C` | `kragInit` |
| `directsound.c` | `0x08046D2C`-`0x08046ED0` | `dsInit`, `getDmaAddress`, `kradActivate`, `kradDeactivate` |
| `mixer.c` | `0x08046ED0`-`0x080471FC` | `kramGetActiveChannels` ... `kramResetChannels` |
| `mixer.arm.c` | `0x080471FC`-`0x080473B4` | `mixRampOut` (ARM, runs from ROM) |
| `player.c` | `0x080473B4`-`0x08049E3C` | `pDataSet` ... `eff_VC_portanote` |
| `stub.S` | `0x08049E3C`-`0x08049E84` | `kram*STUB`, Thumb calls into the IWRAM code |

The game, compiled with GCC 2 (agbcc), cannot make long calls, so it
reaches the IWRAM functions through these stubs (see "Game-side use").

### `.iwram`

| IWRAM | Object | Contents |
|---|---|---|
| `0x03000000` | `directsound.c` | `dsStereo` |
| `0x03000004` | `directsound_asm.S` | `kradInterrupt`, the timer 1 handler |
| `0x03000090` | `mixer.arm.c` | `volMaster[2]`, `hqMode`, `hqRamp`; then `kramPlayExt` (`0x03000094`), `kramPlay` (`0x030002EC`), `kramStop`, `kramSetFreq`, `kramSetVol`, `kramSetPan`, `kramSetPos`, `kramActive` |
| `0x03000604` | `mixer_func.S` | `mixLeft` ... `mix16to8_patch`, `volSumLeft`/`volSumRight` |
| `0x03000C48` | `mixer_private.arm.c` | `mixReal`, `kramWorker` (`0x03001068`), `mixBuffer` (`0x03001144`) |
| `0x03001594` | `player.c` | `iidCounter` |

`ram_symbols.<ver>.inc` names the functions of objects not yet built from
source at their IWRAM addresses; the manifests label their ROM copies with
a `_Rom` suffix. ROM address `X` runs at `0x03000000 + (X - 0x08FB0DB0)`
(US).

`kradInterrupt` counts timer 1 interrupts in `dmaBlock`, restarts the
DirectSound DMA, and on its first call reloads timer 1 with
`65536 - DMABUFFERSIZE`, then overwrites that reload code with `bx lr`.

### `.ewram`

| EWRAM | Object | Contents |
|---|---|---|
| `0x02000000` | `directsound.c` | `lBuffer`, `rBuffer`, `nextSample`, `currMixBlock`, `lastDmaBlock`, `active`, `dmaBlock` |
| `0x020008B4` | `mixer.c` | `channels[32]` (`MixChannel`, 0x2C bytes), `soundTimerCountBackup` |
| `0x02000E38` | `mixer_func.S` | `volClipTable`, indexed -1024..1023 around `0x02001238` |
| `0x02001638` | `mixer_private.arm.c` | `soundTimerFunc`, `soundTimerSpeed`, `soundTimerCount` (both 32768) |
| `0x02001640` | `player.c` | `musicVolume` (128), the player state, `callBack` (`0x020025B4`), `effchns[6]` (`0x020025B8`) |

### `.rodata` (US)

JP has the same layout from `0x08F3C9CC`.

| Range | Object | Contents |
|---|---|---|
| `0x08FA953C`-`0x08FA9568` | `general.c` | `__id`, the `$Id` string |
| `0x08FA9568`-`0x08FA95A8` | `mixer.arm.c` | `mixPanTable[16]` |
| `0x08FA95A8`-`0x08FA980C` | `player.c` | `effects[51]`, `{func1, func2, inbet1}` |
| `0x08FA980C`-`0x08FA985C` | `player.c` | `effectsVC[10]`, `{func, inbet}` |
| `0x08FA985C`-`0x08FAA7CC` | `player_tables.c` | `table_sine`, `table_ramp`, `table_square`, `table_rand`, `table_periods`, `table_finetune`, `table_linear` |

`effects[]` and `effectsVC[]` give the names of the 51 effect handlers;
their `inbet` flags and repeated entries match the public `player.c`
exactly. The word after the tables (`0xFFFFFFFF`, US `0x08FAA7CC`) is
unreferenced and its owner is not known.

## Unmatched objects

Ranges are ROM addresses; RAM images are given by where they are stored.
"Upstream" is the public source at `9a2b869`, compiled unchanged and
compared with `python3 -m tools.krawall.compare` (function by function,
against the ROM function of the same name).

| Object | Section | US | JP |
|---|---|---|---|
| `mixer.c` | `.text` | `0x08046ED0`-`0x080471FC` | `0x08046DFC`-`0x08047128` |
| | `.ewram` | `0x08FB2BFC`-`0x08FB3180` | `0x08F4608C`-`0x08F46610` |
| `mixer.arm.c` | `.text` | `0x080471FC`-`0x080473B4` | `0x08047128`-`0x080472E0` |
| | `.iwram` | `0x08FB0E40`-`0x08FB13B4` | `0x08F442D0`-`0x08F44844` |
| | `.rodata` | `0x08FA9568`-`0x08FA95A8` | `0x08F3C9F8`-`0x08F3CA38` |
| `mixer_private.arm.c` | `.iwram` | `0x08FB19F8`-`0x08FB2344` | `0x08F44E88`-`0x08F457D4` |
| | `.ewram` | `0x08FB3980`-`0x08FB3988` | `0x08F46E10`-`0x08F46E18` |
| `player.c` | `.text` | `0x080473B4`-`0x08049E3C` | `0x080472E0`-`0x08049D68` |
| | `.iwram` | `0x08FB2344`-`0x08FB2348` | `0x08F457D4`-`0x08F457D8` |
| | `.ewram` | `0x08FB3988`-`0x08FB4B40` | `0x08F46E18`-`0x08F47FD0` |
| | `.rodata` | `0x08FA95A8`-`0x08FA985C` | `0x08F3CA38`-`0x08F3CCEC` |

What the comparison shows (US):

- `mixer.c`: upstream matches except `kramResetChannels`,
  `kramQualityMode` (tests `KRAM_QM_RAMP`, like upstream's commented-out
  variant), `kramSetSFXVol` and `kramSetMusicVol` (no `kramResetChannels`
  call). The ROM order is `kramGetActiveChannels`, `kramQualityMode`,
  `kramSetSFXVol`, `kramGetSFXVol`, `kramSetMasterVol`,
  `kramStopSFXChannels`, `kramHandleValid`, `kramGetFreq`, `kramGetVol`,
  `kramGetPan`, `kramGetPos`, `kramSetMusicVol`, `kramSetSoundTimer`,
  `kramSetSoundTimerBPM`, `kramPauseChannels`, `kramUnpauseChannels`,
  `kramStopChannels`, `kramResetChannels`.
- `mixer.arm.c`: `mixRampOut`, `mixPanTable`, `kramStop`, `kramSetFreq`,
  `kramSetVol`, `kramSetPos` and `kramActive` match; `kramPlayExt`,
  `kramPlay` (which follows `kramPlayExt` in the ROM) and `kramSetPan`
  differ. The ROM's IWRAM data before the code is 4 bytes,
  `80 80 00 00` (`volMaster`, `hqMode`, `hqRamp`); upstream initialises
  `hqRamp` to 1 and puts `cidCounter` after it.
- `mixer_private.arm.c`: `mixReal` matches; `kramWorker` is close.
- `player.c`: no function matches; most are 88-97% alike, consistent
  with shifted structure offsets. The function order differs widely.

## Game-side use

Game code includes Krawall's public header, `"3rd_party/krawall.h"`. The
build generates it into `build/include/` the way Krawall's own build
does (`tools/krawall/gen_header.py`): `genheader.pre`, the sections of
`general.h`, `player.h`, `mixer.h` and `directsound.h` between their `%b`
and `//%e` markers, then `genheader.post`. Under GCC 2 it renames the
IWRAM functions to their stubs, so `kramPlay` in game source calls
`kramPlaySTUB`. The sample list is the converter's `samples[]`.

`InitAudio` calls `kragInit(KRAG_INIT_STEREO)`,
`kramSetMasterVol(KRAM_MV_CHANNELS16 | 128)`,
`kramQualityMode(KRAM_QM_HQ)` and `krapCallback(OnKrawallEvent)`; see
`src/sound/`. `OnKrawallEvent` handles only `KRAP_CB_JDONE`. The module and
sample data the player reads are described in
[`../formats/krawall.md`](../formats/krawall.md).
