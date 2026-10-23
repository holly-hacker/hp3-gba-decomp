#pragma once

#include "types.h"

// A screen transition blocks until done. blendArg is the BLDCNT first-target layer mask the
// fade or wipe darkens (or brightens); every caller passes 0x3F.
typedef void (*ScreenTransitionHandler)(u16 blendArg);

// Incoming transitions (g_apfnScreenTransitionsIn), in table order. Each starts from the screen
// its outgoing counterpart left; window wipes show the backdrop inside a window that shrinks off
// the screen.
extern void TransitionInFadeFromBlack(u16 blendArg);
extern void TransitionInFadeFromWhite(u16 blendArg);
extern void TransitionInPaletteFade(u16 blendArg);
extern void TransitionInWipeDown(u16 blendArg);
extern void TransitionInWipeUp(u16 blendArg);
extern void TransitionInWipeRight(u16 blendArg);
extern void TransitionInWipeLeft(u16 blendArg);
extern void TransitionInSplitHorizontal(u16 blendArg);
extern void TransitionInConvergeHorizontal(u16 blendArg);
extern void TransitionInSplitVertical(u16 blendArg);
extern void TransitionInConvergeVertical(u16 blendArg);
extern void TransitionInBoxExpand(u16 blendArg);
extern void TransitionInBoxShrink(u16 blendArg);
extern void TransitionInMosaic(u16 blendArg);
extern void TransitionInLetterbox(u16 blendArg);

// Outgoing transitions (g_apfnScreenTransitionsOut), in table order. Window wipes grow a
// backdrop-only window over the screen, then leave it fully darkened.
extern void TransitionOutFadeToBlack(u16 blendArg);
extern void TransitionOutFadeToWhite(u16 blendArg);
extern void TransitionOutPaletteFade(u16 blendArg);
extern void TransitionOutWipeDown(u16 blendArg);
extern void TransitionOutWipeUp(u16 blendArg);
extern void TransitionOutWipeRight(u16 blendArg);
extern void TransitionOutWipeLeft(u16 blendArg);
extern void TransitionOutSplitHorizontal(u16 blendArg);
extern void TransitionOutConvergeHorizontal(u16 blendArg);
extern void TransitionOutSplitVertical(u16 blendArg);
extern void TransitionOutConvergeVertical(u16 blendArg);
extern void TransitionOutBoxExpand(u16 blendArg);
extern void TransitionOutBoxShrink(u16 blendArg);
extern void TransitionOutMosaic(u16 blendArg);
extern void TransitionOutLetterbox(u16 blendArg);

extern const ScreenTransitionHandler g_apfnScreenTransitionsIn[15];
extern const ScreenTransitionHandler g_apfnScreenTransitionsOut[15];

// Runs g_apfnScreenTransitionsIn[transitionIndex].
extern void PlayScreenTransitionInByIndex(u16 blendArg, u32 transitionIndex);
// Runs g_apfnScreenTransitionsOut[transitionIndex].
extern void PlayScreenTransitionOutByIndex(u16 blendArg, u32 transitionIndex);

// A BLDALPHA coefficient in 8.8 fixed point that TickAlphaBlendRamps moves by wVelocity per
// call, reversing at wMin and wMax.
typedef struct AlphaBlendRamp {
    s16 wValue;
    s16 wVelocity;
    s16 wMin;
    s16 wMax;
} AlphaBlendRamp;

extern AlphaBlendRamp g_AlphaBlendEvaRamp;
extern AlphaBlendRamp g_AlphaBlendEvbRamp;

// Steps both ramps and writes their integer parts to BLDALPHA. Unused, as are the setters of
// the ramp limits and velocities.
extern void TickAlphaBlendRamps(void);
extern void SetAlphaBlendRampLimits(s32 evaMin, s32 evaMax, s32 evbMin, s32 evbMax);
extern void SetAlphaBlendRampVelocities(s32 evaVelocity, s32 evbVelocity);

// Sets BLDALPHA and both ramp values.
extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);
// Sets BLDCNT (layer mask | fade mode) and BLDY (amount, at most 0x10).
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void SetFadeToBlack(u16 layerMask, u16 amount);
// Selects alpha blending with the layers in the `firstTargets` mask as the first target and
// those in `secondTargets` as the second.
extern void SetAlphaBlendTargets(u16 firstTargets, u16 secondTargets);
// Rewrites BLDALPHA from the coefficients SetAlphaBlendCoefficients last set.
extern void CommitAlphaBlendCoefficients(void);

// The BGR555 color TransitionOutPaletteFade fades to, and the step ticks of the palette
// effects that the palette fades and DarkenScreenPalette/RestoreScreenPalette start
// (PaletteEffect.bStepTicks). Set by SetPaletteFadeParams; every caller passes 0, 8.
extern u32 g_dwPaletteFadeColor;
extern u32 g_dwPaletteFadeStepTicks;
extern void SetPaletteFadeParams(u32 color, u32 stepTicks);
// 0x400-byte palette copy: TransitionOutPaletteFade saves BG and OBJ palette RAM there,
// DarkenScreenPalette the BG palette shadow.
extern u16 *g_pScreenPaletteBackup;
// Nonzero while g_pScreenPaletteBackup holds the palette from before DarkenScreenPalette or
// TransitionOutPaletteFade.
extern u32 g_dwScreenPaletteDarkened;
extern void InitScreenTransitionState(void);
extern void DarkenScreenPalette(void);
extern void RestoreScreenPalette(void);
