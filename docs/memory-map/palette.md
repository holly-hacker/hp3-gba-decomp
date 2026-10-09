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
loaded through `sub_0800D6BC` (BG wrapper `sub_0800D244`, OBJ wrapper
`sub_0800D254`): `ApplyGammaToColors` remaps each channel through the gamma table
into the shadow, then DMA3 copies the span to palette RAM. While `0x030022E8`
is nonzero the remapped colors go instead to the 0x400-byte
`g_pPaletteWorkBuffer` and are `CpuSet` to the buffer pointed to by `0x03005624`.
`ApplyGammaRemapTable` makes a table active and re-filters palette RAM and
both shadows in place with it. `g_abGammaNormalRemap` is the identity, so
applying it filters nothing; leaving the high table first filters through
`g_abGammaHighInverseRemap`, its approximate inverse (levels 17, 22, 26 and
29 come back one step brighter). `InitGammaPalette` picks
the table from the save header's `bGammaHigh` flag.

## Animations, PROVEN

`ResetPaletteAnimations` (called by `InitGammaPalette`) clears both animation
tables and empties the OBJ palette load queue (`g_dwObjPaletteQueueCount`,
25 eight-byte `{u16 start, u16 count, src}` entries at `0x030023E8`, filled by
`QueueObjPaletteLoad` and flushed by `sub_0800D354`). `TickPaletteAnimations_candidate`
steps both tables; `sub_0800D304` uploads the entries flagged dirty.

**Color cycles** (`g_aColorCycles`, 12 `ColorCycle` slots). Every
`bDelay + 1` ticks the cycle's current color steps through
`[bStartColor, bEndColor]`, wrapping at either end; `COLOR_CYCLE_REVERSE`
steps downward and `COLOR_CYCLE_PING_PONG` flips the direction at the ends.
The upload copies the shadow to palette RAM rotated so shadow color
`bStartColor` lands at `bCurrentColor`. Slots are handed out sequentially from
`g_dwColorCycleCount` (`sub_0800D784`); `SetupColorCycles` fills one per
`ColorCycleDesc` of a table and sets its bit in `g_dwColorCycleActiveMask`.

**Palette effects** (`g_aPaletteEffects`, 12 `PaletteEffect` slots, counted
by `g_dwPaletteEffectCount`). An effect interpolates a color range toward
16-color frames read from `pFrames`, optionally looping over `bFrameCount`
frames; `sub_0800D5DC` allocates one. Field roles other than flags, color
range, frame count/index and frame pointers are UNCONFIRMED.

Shared flag bits are `PALETTE_ANIM_*` in `include/graphics/palette.h`.
