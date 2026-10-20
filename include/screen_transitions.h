#pragma once

#include "types.h"

typedef void (*ScreenTransitionHandler)(u16 blendArg);

// Indexed by transitionIndex. Entry 2 of the in table (PlayPaletteFadeTransition_candidate) is a
// blocking full-screen palette fade that keeps the normal per-frame tick running.
extern void sub_0803D4A8(u16 blendArg);
extern void sub_0803D508(u16 blendArg);
extern void PlayPaletteFadeTransition_candidate(u16 blendArg);
extern void sub_0803C690(u16 blendArg);
extern void sub_0803D568(u16 blendArg);
extern void sub_0803C714(u16 blendArg);
extern void sub_0803D5E8(u16 blendArg);
extern void sub_0803C798(u16 blendArg);
extern void sub_0803C8DC(u16 blendArg);
extern void sub_0803CA18(u16 blendArg);
extern void sub_0803CB5C(u16 blendArg);
extern void sub_0803CC98(u16 blendArg);
extern void sub_0803CE54(u16 blendArg);
extern void sub_0803CFF4(u16 blendArg);
extern void sub_0803D668(u16 blendArg);
extern void sub_0803D70C(u16 blendArg);
extern void sub_0803D76C(u16 blendArg);
extern void sub_0803C538(u16 blendArg);
extern void sub_0803D7CC(u16 blendArg);
extern void sub_0803D848(u16 blendArg);
extern void sub_0803D8D0(u16 blendArg);
extern void sub_0803D94C(u16 blendArg);
extern void sub_0803C848(u16 blendArg);
extern void sub_0803C96C(u16 blendArg);
extern void sub_0803CAC8(u16 blendArg);
extern void sub_0803CBEC(u16 blendArg);
extern void sub_0803CD7C(u16 blendArg);
extern void sub_0803CF24(u16 blendArg);
extern void sub_0803D164(u16 blendArg);
extern void sub_0803D9D8(u16 blendArg);

extern const ScreenTransitionHandler g_apfnScreenTransitionsIn[15];
extern const ScreenTransitionHandler g_apfnScreenTransitionsOut[15];

// Runs g_apfnScreenTransitionsIn[transitionIndex].
extern void PlayScreenTransitionInByIndex(u32 blendArg, u32 transitionIndex);
// Runs g_apfnScreenTransitionsOut[transitionIndex].
extern void PlayScreenTransitionOutByIndex(u32 blendArg, u32 transitionIndex);

extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);
// Sets BLDCNT (layer mask | fade mode) and BLDY (amount, at most 0x10).
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void SetFadeToBlack(u16 layerMask, u16 amount);
// Selects alpha blending with the layers in the `firstTargets` mask as the first target and
// those in `secondTargets` as the second.
extern void SetAlphaBlendTargets(u16 firstTargets, u16 secondTargets);
// Rewrites BLDALPHA from the coefficients SetAlphaBlendCoefficients last set.
extern void CommitAlphaBlendCoefficients(void);

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
// Nonzero while g_pScreenPaletteBackup holds the palette from before DarkenScreenPalette.
extern u32 g_dwScreenPaletteDarkened;
extern void InitScreenTransitionState_candidate(void);
extern void DarkenScreenPalette(void);
extern void RestoreScreenPalette(void);
