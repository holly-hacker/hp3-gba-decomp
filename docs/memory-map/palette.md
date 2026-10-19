# Palette module — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Code spans
ROM `0x0800D008`-`0x0800DBAC`; every address below is the same in US and JP.

## Palette buffers and gamma, PROVEN

`InitGammaPalette` (called from `AgbMain`) sets up `g_PaletteState` (`PaletteState`,
0x34 bytes at `0x030024B0`):

| Offset | Contents |
|---|---|
| `0x00` | `PaletteBuffer` for BG: 0x200-byte shadow, palette RAM `0x05000000` |
| `0x08` | `PaletteBuffer` for OBJ: 0x200-byte shadow, palette RAM `0x05000200` |
| `0x10` | `u8[32]` active gamma remap, one output level per 5-bit channel value |
| `0x30` | pointer to the ROM remap table copied to `0x10` |

`InitPaletteBuffer` allocates a buffer's shadow with `AllocZeroed`. Colors are
loaded through `LoadPaletteColors` (BG wrapper `LoadBgPaletteColors`, OBJ wrapper
`LoadObjPaletteColors`): `ApplyGammaToColors` remaps each channel through the gamma table
into the shadow, then DMA3 copies the span to palette RAM. While `g_dwPaletteRedirect`
is nonzero the remapped colors go instead to the 0x400-byte
`g_pPaletteWorkBuffer` and are `CpuSet` to `g_pScreenPaletteBackup`.
`ApplyGammaRemapTable` makes a table active and re-filters palette RAM and
both shadows in place with it. `g_abGammaNormalRemap` is the identity, so
applying it filters nothing; leaving the high table first filters through
`g_abGammaHighInverseRemap`, its approximate inverse (levels 17, 22, 26 and
29 come back one step brighter). `InitGammaPalette` picks
the table from the save header's `bGammaHigh` flag; `ToggleGammaRemapTable` switches
between the two.

`UploadPaletteShadows` DMA-copies both shadows to palette RAM. `RestorePalettes`
copies a 0x400-byte BG+OBJ palette into the shadows and palette RAM without gamma,
and `SaveBgPaletteShadow` saves the BG shadow. `FillPalettesWithColor` fills
palette RAM with one gamma-corrected color (`ApplyGammaToColor`), but its
`CpuFastSet` count for each shadow is 1 word, which covers only the first
16 colors.

## Animations, PROVEN

`ResetPaletteAnimations` (called by `InitGammaPalette`) clears both animation
tables and empties the OBJ palette load queue (`g_dwObjPaletteQueueCount`,
25 eight-byte `{u16 start, u16 count, src}` entries at `0x030023E8`, filled by
`QueueObjPaletteLoad` and flushed by `FlushObjPaletteQueue`). `TickPaletteAnimations_candidate`
steps both tables; `UploadPaletteAnimations` uploads the entries flagged dirty.

**Color cycles** (`g_aColorCycles`, 12 `ColorCycle` slots). Every
`bDelay + 1` ticks the cycle's current color steps through
`[bStartColor, bEndColor]`, wrapping at either end; `COLOR_CYCLE_REVERSE`
steps downward and `COLOR_CYCLE_PING_PONG` flips the direction at the ends.
The upload copies the shadow to palette RAM rotated so shadow color
`bStartColor` lands at `bCurrentColor`. Slots are handed out sequentially from
`g_dwColorCycleCount` (`AllocColorCycleSlot`, never reused before a reset);
`StartColorCycle` fills one; `SetupColorCycles` fills one per `ColorCycleDesc`
of a table and sets its bit in `g_dwColorCycleActiveMask`.
`EnableColorCycle`/`DisableColorCycle` toggle `PALETTE_ANIM_ACTIVE` and the mask bit;
disabling can reset the rotation. `UploadColorCycle` performs the rotated upload.

**Palette effects** (`g_aPaletteEffects`, 12 `PaletteEffect` slots, counted
by `g_dwPaletteEffectCount`). An effect interpolates a color range toward
16-color frames read from `pFrames`, optionally looping over `bFrameCount`
frames; `StartPaletteEffect` takes the first inactive slot
(`AllocPaletteEffectSlot`) and returns it, and `StartPaletteEffectWithFrameCount`
and `StartPaletteEffectFromDesc` also set `bFrameCount`. `StopPaletteEffect`
clears a slot; `CompletePaletteEffect` first copies the colors of the first frame
into the shadow and palette RAM.
Field roles other than flags, color range, frame count/index and frame
pointers are UNCONFIRMED.

Shared flag bits are `PALETTE_ANIM_*` in `include/color.h`.

## OBJ palette bank cache, PROVEN

Code in `src/palette/`, declared in `include/palette.h`; it spans US
`0x0803071C`-`0x08030A1C` and JP `0x08030760`-`0x08030A60`.
`g_aObjPaletteSlots` holds one `ObjPaletteSlot` per OBJ palette bank:
the `ObjPalette` loaded there, a refcount and flags. `AttachActorPalette`
reuses a shared slot already holding the palette or allocates one
(`AllocObjPaletteSlot`: empty, then unreferenced, then any shared slot,
else bank 15) and queues colors 1-15 for upload; `AttachActorPaletteUnshared`
always allocates and marks the slot unshared. Screens that load a bank
directly exclude it with `ReserveObjPaletteSlot`.

While an actor is offscreen `TickActor` calls `ReleaseActorPalette`,
which saves the palette and its unshared flag in `pPendingPalette` and drops
the reference; back onscreen, `BindActorPendingPalette` attaches it again.
Overworld actors (room actors, the player, NPCs, wandering monsters) set
their palette this way with `SetActorPendingPalette`, so they take a bank only
while visible. Actors from `SpawnActor` and list menus attach a palette at
once and set `ActorFlagKeepPaletteSlot` to hold it while offscreen. `ActorFlagKeepPaletteSlot` skips both
steps.
