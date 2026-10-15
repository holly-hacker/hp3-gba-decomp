#pragma once

#include "types.h"
#include "gen/graphics/cutscenes.h"
#include "gen/graphics/minigames/hippogriff.h"

// Display registers and BG layers. sub_ names are still unidentified.

extern void ClearPaletteRam(void);

// Per-frame ticks run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickScreenWindows_candidate(void);
extern void TickPaletteAnimations_candidate(void);
extern void TickBgTileAnimations(void);
extern void CommitBgTileAnimations(void);  // run from the vblank callback

// Stops the palette effect with the given handle.
extern void StopPaletteEffect(s32 handle);
// Copies a w x h rectangle of tiles from (srcX, srcY) of a loaded BG tilemap to (dstX, dstY) of the
// given BG, adding tileOffset to the tile numbers and palBank to their palette.
// Starts a palette effect through sub_0800D5DC and sets its bFrameCount; returns its slot.
extern s32 StartPaletteEffectWithFrameCount(u32 startColor, u32 colorCount, u32 stepTicks, u32 delay, u32 flags, const u16 *pFrames, u32 frameCount);
extern s32 QueueObjPaletteLoad(const u16 *pPalette, u32 firstColor, u32 colorCount);  // queues an OBJ palette load (25 max); returns 1 when the queue is full
extern s32 QueueObjPaletteLoadAtOffset(const u8 *pPalettes, u32 byteOffset, u32 firstColor, u32 colorCount);  // QueueObjPaletteLoad from pPalettes + byteOffset
extern void sub_0800D244(const void *pColors, u32 firstColor, u32 colorCount);  // queues a BG palette load
extern void sub_0800D254(const u16 *ptr, s16 val1, s16 val2);
// The colors of a graphic blob's embedded palette, after its two flag bytes
// (see docs/formats/graphic_blob.md).
#define GRAPHIC_BLOB_PALETTE_COLORS(blob) ((const u16 *)((const u8 *)(blob) + 2))
// Dispatches through the 15-entry handler table at 0x0806B844 by transitionIndex. Entry 2
// (0x0803C450) is a blocking full-screen palette fade that keeps the normal per-frame tick running.
extern void PlayScreenTransitionInByIndex(u32 blendArg, u32 transitionIndex);
// Dispatches through the parallel 15-entry handler table at 0x0806B880 by transitionIndex.
extern void PlayScreenTransitionOutByIndex(u32 blendArg, u32 transitionIndex);

extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);
// Sets BLDCNT (layer mask | fade mode) and BLDY (amount, at most 0x10).
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void SetFadeToBlack(u16 layerMask, u16 amount);

// One corner of a hardware window rectangle, positions in 16.16.
typedef struct WindowCorner {
    u16 wFlags;       // bit 1: moving toward the target or drifting
    u16 wFrames;      // frames left in the tween; 0 drifts by the step every frame
    s32 nX;
    s32 nY;
    s32 nStepX;       // per-frame drift, used while wFrames is 0
    s32 nStepY;
    s32 nTargetX;
    s32 nTargetY;
} WindowCorner;

// A hardware window: its top-left and bottom-right corners.
typedef struct ScreenWindow {
    u32 dwFlags;      // bit 0: rectangle changed, needs writing to WINxH/WINxV
    WindowCorner aCorners[2];
} ScreenWindow;
extern ScreenWindow g_aScreenWindows[2];

extern void TickScreenWindow(u32 windowId);

// Hardware windows: layer masks, rectangle (16.16 coordinates), and hiding one.
extern void SetScreenWindowLayers_candidate(u32 windowId, u32 winIn, u32 winOut);
extern void SetScreenWindowRect_candidate(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);
extern void HideScreenWindow_candidate(u32 windowId);



// Allocates a slot in the palette-effect table at 0x030022F8.
extern void sub_0800D5DC(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, const void *pData);
extern void SetAlphaBlendTargets(u8 arg0, u32 arg1);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void FreeBgTileAnimations(void);
extern void PauseBgTileAnimations(void);  // clears bit 1 (running) of every BG tile animation
extern void ResumeBgTileAnimations(void);  // sets bit 1 of every BG tile animation
// One frame of a BG tile animation: its tile data and how many ticks it shows
// (0 holds it).
typedef struct BgTileAnimFrame {
    const void *pTiles;
    u32 dwDuration;
} BgTileAnimFrame;

// A BG tile animation registered by RegisterBgTileAnimation and stepped by
// TickBgTileAnimations; see docs/memory-map/frame_systems.md.
#define BG_TILE_ANIMATION(frameCount) struct {                       \
    u8 bFlags;                                                        \
    u8 bFrameCount;                                                   \
    u16 wUnk2;            /* copied into the animation's entry */     \
    u32 dwBufferSize;     /* bytes allocated for the decoded tiles */ \
    BgTileAnimFrame aFrames[frameCount];                              \
}

// The fixed head of every BG_TILE_ANIMATION.
typedef struct BgTileAnimHeader {
    u8 bFlags;
    u8 bFrameCount;
    u16 wUnk2;
    u32 dwBufferSize;
} BgTileAnimHeader;

// The low bits of a BG control word as stored in ROM (the BGxCNT layout).
typedef struct BgControlWord {
    u32 bPriority : 2;
    u32 bCharBlock : 2;  // 16 KB character block holding the BG's tiles
    u32 dwRest : 28;
} BgControlWord;

// Runtime state of one registered BG tile animation.
typedef struct BgTileAnimEntry {
    u8 bFlags;  // 1 active, 2 running, 4 tiles pending upload, 8 buffer is uploaded in one piece
    u8 pad_01;
    u8 bFrame;
    u8 bTimer;
    u16 wTileOffset;  // first tile in the character block
    u16 pad_06;
    const BgTileAnimHeader *pAnimation;
    const BgControlWord *pBgControl;
} BgTileAnimEntry;

extern u8 g_bBgTileAnimationCount;
extern BgTileAnimEntry g_aBgTileAnimations[4];
extern void *g_apBgTileAnimationBuffers[4];  // decoded tiles of each entry

typedef BG_TILE_ANIMATION(16) BgTileAnimation16;
typedef BG_TILE_ANIMATION(64) BgTileAnimation64;
typedef BG_TILE_ANIMATION(128) BgTileAnimation128;

// Scene-effect resources selected by room-script opcode 0x33.
extern const BgTileAnimation128 g_aSpecialSceneBg2;  // 0x08063074
extern const BgTileAnimation128 g_aSpecialSceneBg0;  // 0x0806347C
extern const BgTileAnimation128 g_aSpecialSceneBg1;  // 0x08063884
extern const u32 g_dwSpecialSceneBgControl;          // 0x0805BC00

extern const u32 g_dwStartupBg3Control;
extern const u32 g_dwStartupBg2Control;
extern const u32 g_dwStartupBg1Control;

// The write-only half of SetBgControl: writes BGxCNT and the tilemap/charblock
// VRAM bases, without enabling the layer via SetDispcntFlag.
extern void SetBgControlRegister(u32 bg, u32 control);
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
extern void InitDisplayControl(void);
