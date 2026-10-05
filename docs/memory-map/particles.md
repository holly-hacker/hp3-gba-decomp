# Particle emitters — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Addresses are US;
JP addresses are in the table below. The matched C is authoritative:
`include/graphics/graphics.h` (`ParticleEmitter`, `Particle`, flag and mode enums) and
`src/graphics/`.

## Structure — PROVEN (byte-matched C)

An **emitter** is a `0x4C`-byte record; a **particle** is a `0x48`-byte record whose
`OamEntry` sits at `+0x24`. Both come from fixed pools through
`AllocObjectFromFreeList` (zeroed on allocation).

| | Active list | Free list | Count | Limit |
|---|---|---|---|---|
| Emitters | `g_pParticleEmitterActiveListHead` | `g_pParticleEmitterFreeListHead` | `g_wActiveParticleEmitterCount` | 9 |
| Particles | `g_pParticleActiveListHead` | `g_pParticleFreeListHead` | `g_wActiveParticleCount` | `0x3F` |

`g_wParticleEmitterHighWaterMark` and `g_wParticleHighWaterMark` track the peaks.
`g_apParticleGfxPools[pool][entry]` (`ParticleGfxEntry`, `0x2C` bytes) supplies an
emitter's tile allocation, sprite and animation data. `g_bParticleSpawnBlocked` is set by
the per-particle update when its OAM submit fails (queue full) and cleared at the end of
`TickParticleEmitters`.

| Function | Address | Source |
|---|---|---|
| `AllocParticleEmitter` | `0x08030B70` | `src/graphics/particle/alloc_particle_emitter.c` |
| `TickParticleEmitter` | `0x08030C9C` | `src/graphics/particle/tick_particle_emitter.c` |
| `SpawnParticle` | `0x08030D90` | `src/graphics/particle/spawn_particle.c` |
| `ReleaseParticleEmitter_candidate` | `0x080316A4` | `src/graphics/particle/release_particle_emitter.c` |
| `InitResourceCachePools` | `0x080315A4` | `src/graphics/particle/init_resource_cache_pools.c` |
| `ResetParticleState` | `0x08031624` | `src/graphics/particle/reset_particle_state.c` |
| `FreeAllParticleEmitters` | `0x080316D4` | `src/graphics/particle/free_all_particle_emitters.c` |
| `FreeAllParticles` | `0x0803171C` | `src/graphics/particle/free_all_particles.c` |
| `ReleaseParticle` | `0x08031848` | `src/graphics/particle/release_particle.c` |
| `TickParticleEmitters` | `0x08031748` | `src/graphics/particle/tick_particle_emitters.c` |
| `CreateMenuCursorEmitter` | `0x0801DBE0` | `src/graphics/particle/create_menu_cursor_emitter.c` |
| `FixedMultiply` | `0x0802BEE8` | asm; `((a >> 6) * (b >> 6)) >> 4` |

JP addresses (same sources, byte-matched): `CreateMenuCursorEmitter` `0x0801DBDC`,
`AllocParticleEmitter` `0x08030BB4`, `TickParticleEmitter` `0x08030CE0`, `SpawnParticle`
`0x08030DD4`, `TickParticleEmitters` `0x0803178C`, `InitResourceCachePools` `0x080315E8`,
`ResetParticleState` `0x08031668`, `FreeAllParticleEmitters` `0x08031718`, `FreeAllParticles`
`0x08031760`, `ReleaseParticle` `0x0803188C`, `FixedMultiply` `0x0802BF44`. The RAM symbols
sit `0x60` higher than US (for example `g_pParticleEmitterActiveListHead` is `0x030051F8`);
`g_pMenuCursorEmitter` is `0x030028C0` in both.

Not yet decompiled: the per-particle update `sub_08031358`, the particle OAM submit
`sub_0803186C`, and the graphics pool teardown `sub_08031668`.
The bytes at `0x08031798`-`0x080317EC` are an unseeded function.

## Per-frame flow

`TickFrameSystems` (see [`frame_systems.md`](frame_systems.md)) calls `TickParticleEmitters`,
and so do the battle script wait handlers. It walks the active list; an emitter with
`ParticleEmitterFlagSkipTick` is not ticked, and that bit is cleared on every emitter.

`TickParticleEmitter` then:

1. Counts `wSpawnTimer` up; it fires when the old value is `>= wSpawnPeriod`, so every
   `wSpawnPeriod + 1` ticks, and resets it.
2. On a fire, makes up to `bSpawnsPerPeriod` attempts. An attempt needs
   `g_wActiveParticleCount <= 0x3E`, `g_bParticleSpawnBlocked == 0`, no
   `ParticleEmitterFlagSpawnDisabled`, and either the target object onscreen
   (`ObjectFlagOnscreenForTileAlloc`) or `ParticleEmitterFlagScreenPosition`.
3. With `ParticleEmitterFlagSpawnRoll`, an attempt spawns only if
   `Mt19937RandMax2(wSpawnRollMax) < wSpawnRollThreshold` (cursor 2).
4. Releases the emitter when the target has `ObjectFlagPendingDestroy`, or when
   `ParticleEmitterFlagRelease` is set and `wDuration` counts down past zero.

## RNG use of one spawn — PROVEN

Cursor 2 is the visual cursor, cursor 1 the gameplay cursor (see [`rng.md`](rng.md)).
Draws happen in this order:

| Step | Draw | Cursor |
|---|---|---|
| Spawn roll (per attempt, only with `SpawnRoll`) | `RandMax2(wSpawnRollMax)` | 2 |
| Segment spawn (mode 4 or 5, not `ScreenPosition`) | `RandRange2(0, 0xFFFF)` | 2 |
| Position x, then y | `RandRange2(pos - wSpread, pos + wSpread)` | 2 |
| Lifetime | `wLifetimeRange == 0`: `RandRange2(1, 5)`; `== 5`: none; else `RandRange2(wLifetimeRange, 5)`; each added to `wLifetimeBase` | 2 |
| Mode 2 and 5 direction | `RandRange2(0, 7)` | 2 |
| Mode 6 x velocity, then y velocity | `RandRange(abVelRange[0] << 8, abVelRange[1] << 8) * 4`, then `-(RandRange(abVelRange[2] << 12, abVelRange[3] << 12) * 2)` | **1** |
| Mode 7 and 8 speed | `RandMax((u16)dwSpeed) << 8` | **1** |

`Mt19937RandRange` returns its minimum without drawing when `min == max`, so a mode 6
axis with equal bounds consumes nothing. `dwSpeed` defaults to `0x20000`, whose low half is
0; `RandMax(0)` still consumes a draw and returns 0.

## Main menu cursor emitter — PROVEN

`ShowMainMenuEntries_candidate` builds the cursor object with `sub_0801D940(4)`, whose kind-4
branch calls `CreateMenuCursorEmitter`. The emitter is released by `ExitMainMenuScreen` through
`sub_0801DC6C`. Configuration, from the matched C:

| Field | Value |
|---|---|
| `wSpawnPeriod` | 5 (fires every 6 frames) |
| `wFlags` | `0xC84`: `SpawnRoll` plus bits `0x400`, `0x80`, `0x04` |
| Spawn roll | `RandMax2(0x1000) < 0x800`: 16381 of 32768 draws pass (about 49.99%) |
| `bMode` | 6 (random velocity, `abVelRange` = -40, 40, 0, 0) |
| `wLifetimeBase`, `wLifetimeRange` | `0x23`, 5 (fixed 40-frame lifetime, no draw) |
| `wSpread` | 1 |
| Spawn position | the cursor object's integer position (no `Mt19937` draw for the base point) |

Each fire that passes the gates therefore costs one cursor-2 roll, and a successful roll
costs three more cursor-2 draws (x, y) plus **one cursor-1 draw**, the x velocity; the y
range is 0 to 0, so it draws nothing. On average the menu advances the gameplay cursor once
per 12 frames while the cursor is on screen. On the boot path the emitter is created after the
`Mt19937AutoSeed` call in `UpdateMainMenu`, so those draws follow the seed directly.

## Cursor 2 in the main menu — STRUCTURAL MATCH

Derived from a static call graph over direct `bl` edges only. Indirect calls (object tick
pointers, animation opcodes, interrupt handlers) are not followed, and nothing was checked in an
emulator.

- `PlaySoundById` (`0x0803FC68`, `src/audio/play_sound_by_id.c`) reads `g_aSoundConfig[id]`
  (`0x08FB09F8`). A `SoundModeSample` row plays a sample with no RNG. A `SoundModeVariants` row draws
  `Mt19937RandMax2(7)` to pick one of 8 variants from `g_aSoundVariants`. The tables are in
  `src/audio/`. Variant-row ids below `0x100`: `0x18`, `0x20`,
  `0x3A`, `0x3C`, `0x8C`, `0x9B`, `0x9D`, `0x9F`, `0xA0`, `0xA2`, `0xA3`, `0xA5`, `0xA6`, `0xA8`,
  `0xA9`.
- The sounds reachable from the main menu are `0` (cursor move), `1` (START and select) and `0x47`
  (`TickObject`, when an object's position changed). All are sample rows. The boot path before the menu
  plays `0`, `1` and `2` in the language select, also sample rows. `sub_0803FD04` has no direct-call path
  from the menu. The cursor's animation streams (`0x0805E0D0`, `0x0805E0E0`) contain no `0xFD`
  sound opcode (`sub_080021F4` case 14 plays `PlaySoundById`).
- No other `Mt19937*` caller is reachable from the menu. `Mt19937AutoSeed` (on START) and the emitter
  are the only ones on the boot path.

So on the boot path, after `Mt19937AutoSeed`, the emitter is the only thing that advances either
cursor. Per fire (every 6th frame while the cursor object is onscreen) cursor 2 consumes one draw for
the spawn roll, plus two more on a pass; cursor 1 consumes one on a pass. Both cursors read the same
seeded array from word 1 until cursor 1's first regeneration (`Mt19937SetSeed` sets its remaining
count to `MT_N - 1`), so cursor 2's first roll tempers the same word as cursor 1's first draw.
Cursor 2's variables start zeroed (`ClearSystemMemory` fills IWRAM from `0x03001598` to
`0x03007D00`, which includes `0x03005588`/`0x0300558C`), so its first `Mt19937Next2` wraps to
`state + 1`. Entering the menu from elsewhere in the game (not the boot path) depends on cursor 2's
earlier history, which this analysis does not cover.

## Open questions

- Meaning of `wParam38` beyond mode 6, the emitter flags `0x80` and `0x400`, and
  `ParticleEmitterFlagPriorityBelow_candidate`'s stale-priority read (particles start zeroed, so
  that branch always yields priority 0).
- The neighbouring particle code (`sub_08031358`, `sub_0803186C`, teardown) is still assembly in both versions.
