#pragma once

#include "types.h"

// Dispatches through the 15-entry handler table at 0x0806B844 by transitionIndex. Entry 2
// (0x0803C450) is a blocking full-screen palette fade that keeps the normal per-frame tick running.
extern void PlayScreenTransitionInByIndex(u32 blendArg, u32 transitionIndex);
// Dispatches through the parallel 15-entry handler table at 0x0806B880 by transitionIndex.
extern void PlayScreenTransitionOutByIndex(u32 blendArg, u32 transitionIndex);

extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);
// Sets BLDCNT (layer mask | fade mode) and BLDY (amount, at most 0x10).
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void SetFadeToBlack(u16 layerMask, u16 amount);
// Selects alpha blending with the layers in the `firstTargets` mask as the first target and
// those in `secondTargets` as the second.
extern void SetAlphaBlendTargets(u16 firstTargets, u16 secondTargets);

// Set by SetScreenDarkenParams_candidate (every caller passes 0, 8).
// DarkenScreenPalette and RestoreScreenPalette pass the step ticks to the
// palette effect they start (PaletteEffect.bStepTicks_candidate); no reader
// of g_dwUnk03005638 has been found.
extern u32 g_dwUnk03005638;
extern u32 g_dwScreenDarkenStepTicks_candidate;
extern void SetScreenDarkenParams_candidate(u32 arg0, u32 stepTicks);
// 0x400-byte copy of the BG+OBJ palette that DarkenScreenPalette saves and
// RestoreScreenPalette restores.
extern u16 *g_pScreenPaletteBackup;
extern void InitScreenTransitionState_candidate(void);
extern void DarkenScreenPalette(void);
extern void RestoreScreenPalette(void);
