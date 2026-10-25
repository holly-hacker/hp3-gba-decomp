#pragma once

#include "types.h"

// Palette module: gamma-corrected shadow
// palettes, color cycling and palette effects.

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
    u8 bColorCountCopy;  // written equal to bColorCount, never read
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
    u8 bStepTicks;
    u8 bStepTimer;
    u8 bDelayTimer;
    u8 bDelay;
    u8 bStartColor;
    u8 bEndColor;
    u8 bFrameCount;
    u8 bFrameIndex;
    u16 wColorCount;
    const u16 *pFrames;
    const u16 *pCurrentFrame;
} PaletteEffect;

// StartPaletteEffectFromDesc's arguments.
typedef struct PaletteEffectDesc {
    const u16 *pFrames;
    u8 bStartColor;
    u8 bColorCount;
    u8 bStepTicks;
    u8 bDelay;
} PaletteEffectDesc;

// A pending OBJ palette load: wColorCount colors from pPalette into OBJ palette RAM starting at
// color firstColor.
typedef struct ObjPaletteQueueEntry {
    u16 wFirstColor;
    u16 wColorCount;
    const u16 *pPalette;
} ObjPaletteQueueEntry;

// Nonzero while palette loads go to g_pPaletteWorkBuffer instead of palette RAM.
extern u32 g_dwPaletteRedirect;
extern u16 *g_pPaletteWorkBuffer;            // 0x030022EC
extern PaletteState g_PaletteState;          // 0x030024B0
extern ColorCycle g_aColorCycles[12];        // 0x03002280
extern u32 g_dwColorCycleActiveMask;         // 0x030022E0
extern u32 g_dwColorCycleCount;              // 0x030022E4
extern u32 g_dwObjPaletteQueueCount;         // 0x030022F0
extern u32 g_dwPaletteEffectCount;           // 0x030022F4
extern PaletteEffect g_aPaletteEffects[12];  // 0x030022F8
extern ObjPaletteQueueEntry g_aObjPaletteQueue[25];  // 0x030023E8


extern const u8 g_abUnusedColorZeros[8];
extern const u8 g_abGammaNormalRemap[32];
extern const u8 g_abGammaHighRemap[32];
// Approximate inverse of g_abGammaHighRemap, used to undo it.
extern const u8 g_abGammaHighInverseRemap[32];

extern void ApplyGammaRemapTable(const u8 *pTable);
extern void InitGammaPalette(void);
extern u16 *ApplyGammaToColors(u16 *pDst, const u16 *pSrc, u32 size);
extern void RestorePalettes(const u16 *pColors);
extern void LoadBgPaletteColors(const void *pColors, u32 firstColor, u32 colorCount);
extern void LoadObjPaletteColors(const u16 *pColors, u32 firstColor, u32 colorCount);
extern s32 QueueObjPaletteLoad(const u16 *pPalette, u32 firstColor, u32 colorCount);  // queues an OBJ palette load (25 max); returns 1 when the queue is full
extern s32 QueueObjPaletteLoadAtOffset(const u8 *pPalettes, u32 byteOffset, u32 firstColor, u32 colorCount);  // QueueObjPaletteLoad from pPalettes + byteOffset
extern void TickPaletteAnimations(void);  // run by TickFrameSystems
extern void UploadPaletteAnimations(void);
extern void FlushObjPaletteQueue(void);
extern void ClearPaletteRam(void);
extern void FillPalettesWithColor(u32 color);
extern void UploadPaletteShadows(void);
extern void SaveBgPaletteShadow(u16 *pDst);
extern void ToggleGammaRemapTable(void);
extern u32 StartColorCycle(u32 startColor, u32 colorCount, u32 delay, u32 flags);
extern void SetColorCycleFlagsAndDelay(u32 slot, u32 delay, u32 flags);
extern void EnableColorCycle(u8 slot);
extern void DisableColorCycle(u8 slot, u32 resetColors);
// Starts a palette effect through StartPaletteEffect and sets its bFrameCount; returns its slot.
extern s32 StartPaletteEffectWithFrameCount(u32 startColor, u32 colorCount, u32 stepTicks, u32 delay, u32 flags, const u16 *pFrames, u32 frameCount);
extern s32 StartPaletteEffectFromDesc(const PaletteEffectDesc *pDesc, u32 flags, u32 frameCount);
extern s32 StartPaletteEffect(u32 startColor, u32 colorCount, u32 stepTicks, u32 delay, u32 flags, const u16 *pFrames);
// Stops the palette effect with the given handle.
extern void StopPaletteEffect(s32 handle);
extern void CompletePaletteEffect(s32 handle);
extern void InitPaletteBuffer(PaletteBuffer *pBuffer, volatile u16 *pPaletteRam);
extern void LoadPaletteColors(const u16 *pColors, u32 firstColor, u32 colorCount, PaletteBuffer *pBuffer);
extern u16 ApplyGammaToColor(u16 color);
extern u32 AllocColorCycleSlot(void);
extern void ResetPaletteAnimations(void);
extern void SetupColorCycles(const ColorCycleTable *pTable);
extern void ResetColorCycles(void);
extern void ClearColorCycle(ColorCycle *pCycle);
extern void ResetPaletteEffects(void);
extern void ClearPaletteEffect(PaletteEffect *pEffect);
extern void TickColorCycles(void);
extern void StepColorCycle(ColorCycle *pCycle);
extern void UploadColorCycle(ColorCycle *pCycle);
extern u32 AllocPaletteEffectSlot(void);
extern void TickPaletteEffects(void);
extern void StepPaletteEffect(PaletteEffect *pEffect);
extern void UploadPaletteEffect(PaletteEffect *pEffect);
