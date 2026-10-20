# Screen transitions — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Addresses are US;
JP is `0x68` higher for the whole block (US `0x0803C3BC`-`0x0803DA4C`). The matched C
in `src/screen_transitions/` and `include/screen_transitions.h` is authoritative.

## Playing a transition, PROVEN

`PlayScreenTransitionInByIndex`/`PlayScreenTransitionOutByIndex` set
`GameModeFlagScreenTransition` (and `GameModeFlagScreenTransitionOut` for the out
table) in `g_dwGameModeFlags`, run entry `transitionIndex` of
`g_apfnScreenTransitionsIn`/`g_apfnScreenTransitionsOut` (`0x0806B844`/`0x0806B880`),
then clear the flags. Each handler blocks until it finishes. Its argument is the
BLDCNT first-target layer mask the fade applies to; every caller passes `0x3F`.

| Index | Effect | In: reveals | Out: covers |
|---|---|---|---|
| 0 | BLDY fade, black | 16 to 0 | 0 to 14 |
| 1 | BLDY fade, white | 16 to 0 | 0 to 16 |
| 2 | palette fade | to the target palette | to `g_dwPaletteFadeColor` |
| 3-6 | wipe down, up, right, left | | |
| 7 | split from the center column | | |
| 8 | converge on the center column | | |
| 9 | split from the center row | | |
| 10 | converge on the center row | | |
| 11 | box expanding from the center | | |
| 12 | box shrinking to the center | | |
| 13 | mosaic, with a BLDY fade | 15x15 to none | none to 15x15 |
| 14 | letterbox bars | adds them | fades, removes them |

The BLDY fades, palette fades, mosaics and letterbox keep the scene running: each
step runs the `TickFrameSystems` ticks (except the overworld pause-menu check)
and waits two frames. Window wipes only wait one frame per step; they move edges
2 lines or 3 pixels a step. A wipe window shows only the backdrop, except for the
in-box-expand and out-box-shrink windows, which show the layers and blank the
outside. Out wipes end with BLDY at 16, so the screen stays black after the
windows turn off.

The mosaics set the BGxCNT mosaic bit of every displayed BG and `oam.mosaic` of
every active actor; they clear the actors' bits afterwards but leave the BG bits
set. The in-letterbox fade has no visible effect: WINOUT `0x1F` disables color
effects outside the bars.

## Palette fades and darkening, PROVEN

`SetPaletteFadeParams` sets `g_dwPaletteFadeColor` and `g_dwPaletteFadeStepTicks`
(every caller passes black, 8 ticks). Out 2 copies palette RAM to
`g_pScreenPaletteBackup`, sets `g_dwScreenPaletteDarkened` and the palette
redirect, and fades BG and OBJ palettes to the solid color. The redirect stays on,
so the next mode's palette loads land in `g_pPaletteWorkBuffer`. In 2 fades to the
work buffer, after first refilling it from the backup if `g_dwScreenPaletteDarkened`
is set (clearing it), or from palette RAM if no redirect is active.

`DarkenScreenPalette` (battle script opcode `0xA5`) saves the BG palette shadow to
the backup and fades the BG palette to half brightness; `RestoreScreenPalette`
(`0xA6`) fades back to the backup.

## Alpha-blend ramps, PROVEN

`g_AlphaBlendEvaRamp`/`g_AlphaBlendEvbRamp` hold the BLDALPHA coefficients in 8.8
fixed point. `SetAlphaBlendCoefficients` sets them and BLDALPHA;
`CommitAlphaBlendCoefficients` rewrites BLDALPHA from them. `TickAlphaBlendRamps`,
`SetAlphaBlendRampLimits` and `SetAlphaBlendRampVelocities` would bounce them
between limits, but nothing calls them.
