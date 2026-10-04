#pragma once

#include "types.h"

// Palette module (ROM 0x0800D008-0x0800DBAC): gamma-corrected shadow
// palettes, color cycling and palette effects. See docs/memory-map/palette.md.

// A RAM shadow of one 0x200-byte palette half and the palette RAM it is
// uploaded to.
typedef struct PaletteBuffer {
    u16 *pShadow;
    volatile u16 *pPaletteRam;  // BG_PLTT or OBJ_PLTT
} PaletteBuffer;

typedef struct PaletteState {
    PaletteBuffer bg;
    PaletteBuffer obj;
    u8 abGammaRemap[32];      // output level for each 5-bit channel value
    const u8 *pGammaTable;    // ROM table copied into abGammaRemap
} PaletteState;

// Flags shared by ColorCycle.bFlags and PaletteEffect.wFlags.
#define PALETTE_ANIM_ACTIVE 0x01
#define PALETTE_ANIM_DIRTY  0x02  // the shadow changed; upload it this frame
#define PALETTE_ANIM_OBJ    0x04  // OBJ palette instead of BG

// ColorCycle.bFlags only.
#define COLOR_CYCLE_PING_PONG 0x10  // flip COLOR_CYCLE_REVERSE at either end
#define COLOR_CYCLE_REVERSE   0x20  // step from bEndColor down to bStartColor

// Rotates palette colors [bStartColor, bEndColor] by one entry every
// bDelay + 1 ticks.
typedef struct ColorCycle {
    u8 bFlags;
    u8 bDelay;
    u8 bTimer;
    u8 bStartColor;
    u8 bCurrentColor;
    u8 bEndColor;
    u8 bColorCount;
    u8 bColorCount2_candidate;  // written equal to bColorCount, never seen read
} ColorCycle;

// A color-cycle request in a ColorCycleTable.
typedef struct ColorCycleDesc {
    u8 bStartColor;
    u8 bColorCount;
    u8 bDelay;
    u8 bFlags;
} ColorCycleDesc;

typedef struct ColorCycleTable {
    u16 wCount;
    u16 wUnused;
    ColorCycleDesc aCycles[1];
} ColorCycleTable;

// Interpolates colors [bStartColor, bEndColor] toward 16-color frames read
// from pFrames, looping over bFrameCount frames when flag 0x10 is set.
typedef struct PaletteEffect {
    u16 wFlags;
    u8 bStepTicks_candidate;
    u8 bStepTimer_candidate;
    u8 bDelayTimer_candidate;
    u8 bDelay_candidate;
    u8 bStartColor;
    u8 bEndColor;
    u8 bFrameCount;
    u8 bFrameIndex;
    u16 wColorCount;
    const u16 *pFrames;
    const u16 *pCurrentFrame;
} PaletteEffect;

extern u16 *g_pPaletteWorkBuffer;            // 0x030022EC
extern PaletteState g_PaletteState;          // 0x030024B0
extern ColorCycle g_aColorCycles[12];        // 0x03002280
extern u32 g_dwColorCycleActiveMask;         // 0x030022E0
extern u32 g_dwColorCycleCount;              // 0x030022E4
extern u32 g_dwObjPaletteQueueCount;         // 0x030022F0
extern u32 g_dwPaletteEffectCount;           // 0x030022F4
extern PaletteEffect g_aPaletteEffects[12];  // 0x030022F8

extern const ColorCycleTable g_ColorCyclesDefault;
extern const ColorCycleTable g_ColorCyclesRoom12;

extern void InitGammaPalette(void);
extern u16 *ApplyGammaToColors(u16 *pDst, const u16 *pSrc, u32 size);
extern void InitPaletteBuffer(PaletteBuffer *pBuffer, volatile u16 *pPaletteRam);
extern void ResetPaletteAnimations(void);
extern void SetupColorCycles(const ColorCycleTable *pTable);
extern void ResetColorCycles(void);
extern void ClearColorCycle(ColorCycle *pCycle);
extern void ResetPaletteEffects(void);
extern void ClearPaletteEffect(PaletteEffect *pEffect);
