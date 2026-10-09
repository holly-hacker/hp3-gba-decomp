#pragma once

#include "types.h"
#include "gen/graphics/cutscenes.h"
#include "gen/graphics/minigames/hippogriff.h"

// Display registers and BG layers. sub_ names are still unidentified.

extern void ClearVram(void);
extern void ClearPaletteRam(void);
extern void ClearOamDma(void);
extern void ClearPaletteRamDma(void);
// ClearVram, ClearOamDma, then ClearPaletteRamDma.
extern void ClearVideoMemory(void);

// Per-frame ticks run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickBgLayers_candidate(void);
extern void TickScreenWindows_candidate(void);
extern void TickPaletteAnimations_candidate(void);
extern void TickBgTileAnimations(void);
extern void CommitBgTileAnimations(void);  // run from the vblank callback

// Per-BG scroll/affine state, 0x6C bytes per BG starting at g_aBgScrollState.
typedef struct BgScrollState {
    u8 pad_00[0x08];
    void *pBgGraphicResult_candidate;  // 0x08, LoadBgGraphic's result for this BG, as stored by the owl care screen
    u8 pad_0C[0x10];
    u32 dwFlags;                 // 0x1C, bit 0x8000 asks for a scroll update
    u8 pad_20[0x08];
    u32 nScrollY_candidate;      // 0x28, 16.16
    u8 pad_2C[0x40];
} BgScrollState;
extern BgScrollState g_aBgScrollState[];  // 0x03001E80; [1].nScrollY_candidate == 0x03001F14
// State of one BG layer, 0x6C bytes per layer starting at g_aBgLayers. The same array that
// g_aBgScrollState addresses four bytes earlier.
typedef struct BgLayer {
    u8 pad_00[0x18];
    u32 dwFlags;       // 0x18: BG_LAYER_*
    s32 nOutX;         // 0x1C: 16.16 scroll written to BGxHOFS
    s32 nOutY;         // 0x20: 16.16 scroll written to BGxVOFS
    s32 nScrollX;      // 0x24: 16.16
    s32 nScrollY;      // 0x28: 16.16
    s32 nStepX;        // 0x2C: per-frame scroll step, used when the tween has no frames
    s32 nStepY;        // 0x30
    s32 nTargetX;      // 0x34: tween target
    s32 nTargetY;      // 0x38
    u16 wTweenFrames;  // 0x3C: frames left; 0 steps by nStep each frame
    u16 wZoom;         // 0x3E: 8.8
    s16 nZoomStep;     // 0x40: per-frame change
    s16 nZoomMin;      // 0x42
    s16 nZoomMax;      // 0x44
    u16 wAngle;        // 0x46: the high byte indexes g_anSineTable
    u16 wAngleStep;    // 0x48
    s16 nCenterX;      // 0x4A: rotation centre offset in pixels
    s16 nCenterY;      // 0x4C
    s16 nPa;           // 0x4E: BG affine matrix, 8.8
    s16 nPb;           // 0x50
    s16 nPc;           // 0x52
    s16 nPd;           // 0x54
    u8 pad_56[0x02];
    s32 nRefX;         // 0x58: BG affine reference point
    s32 nRefY;         // 0x5C
    u16 wWobblePhaseX; // 0x60
    u16 wWobblePhaseY; // 0x62
    s16 nWobbleSpeedX; // 0x64
    s16 nWobbleSpeedY; // 0x66
    s16 nWobbleAmpX;   // 0x68
    s16 nWobbleAmpY;   // 0x6A
} BgLayer;
extern BgLayer g_aBgLayers[4];  // 0x03001E84

#define BG_LAYER_TWEEN        0x0001  // scroll toward nTarget over wTweenFrames
#define BG_LAYER_ROTATE       0x0002  // advance wAngle by wAngleStep
#define BG_LAYER_ZOOM_BOUNCE  0x0004  // bounce wZoom between nZoomMin and nZoomMax
#define BG_LAYER_WOBBLE       0x0008  // sine wobble added to the output scroll
#define BG_LAYER_MATRIX_DIRTY 0x4000  // rebuild the affine matrix and reference point
#define BG_LAYER_COMMIT       0x8000  // write the scroll registers at the next vblank

extern void ApplyBgLayerWobble(u32 bg);
// Adds (dx, dy) to the two-word point.
extern void AddOffsetToPoint(s32 dx, s32 dy, s32 *pPoint);
extern u8 g_abBgPriority[];     // 0x03003F8C; [4] == 0x03003F90

// Stops the palette effect with the given handle.
extern void StopPaletteEffect(s32 handle);
// Copies a w x h rectangle of tiles from (srcX, srcY) of a loaded BG tilemap to (dstX, dstY) of the
// given BG, adding tileOffset to the tile numbers and palBank to their palette.
extern void sub_0800D57C(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, const void *pData, u32 arg6);  // palette fade/cycle effect
extern void sub_08006C00(u32 bg, const void *pTilemap, u32 tileOffset, u32 palBank, u32 srcX, u32 srcY,
                         u32 dstX, u32 dstY, u32 width, u32 height);
extern s32 QueueObjPaletteLoad(const u16 *pPalette, u32 firstColor, u32 colorCount);  // queues an OBJ palette load (25 max); returns 1 when the queue is full
extern void sub_0800D254(const u16 *ptr, s16 val1, s16 val2);
extern void LoadEmbeddedPalette_candidate(u8 *blob, s32 paletteRowOffset, s32 rowCount);
// The colors of a graphic blob's embedded palette, after its two flag bytes
// (see docs/formats/graphic_blob.md).
#define GRAPHIC_BLOB_PALETTE_COLORS(blob) ((const u16 *)((const u8 *)(blob) + 2))
// Dispatches through the 15-entry handler table at 0x0806B844 by transitionIndex. Entry 2
// (0x0803C450) is a blocking full-screen palette fade that keeps the normal per-frame tick running.
extern void PlayScreenTransitionInByIndex(u32 blendArg, u32 transitionIndex);
// Dispatches through the parallel 15-entry handler table at 0x0806B880 by transitionIndex.
extern void PlayScreenTransitionOutByIndex(u32 blendArg, u32 transitionIndex);

// ORs into / clears DISPCNT bits.
extern void SetDispcntFlag(u32 flags);
// Writes BGxCNT for BG `bg` and enables the layer.
extern void SetBgControl(u32 bg, u32 control);
extern void EnableBg(u32 bg);
extern void DisableBg(u32 bg);
extern void SetBgPriority(u32 bg, u8 priority);
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

extern void ResetDisplayState(u32 arg);
extern void FillBgTilemap_candidate(u32 bg, u32 arg1, u32 arg2);
extern void ClearBgTilemap(u32 bg);

extern void sub_08007AF0(u32 bg, u32 arg1, u32 arg2);
extern void sub_08007C2C(u32 bg, u32 arg1, u32 arg2);
extern void sub_08007C94(u32 bg, s32 arg1, u32 arg2);
extern void sub_08007CF4(u32 bg, s32 arg1);
extern void sub_08007D14(u32 bg, u32 arg1, u32 arg2);
extern void sub_08007D60(u32 bg, s32 arg1);
extern void sub_08007F84(u32 bg, s32 *pOut0, s32 *pOut1);

// Allocates a slot in the palette-effect table at 0x030022F8.
extern void sub_0800D5DC(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, const void *pData);
extern void *LoadBgGraphic(u32 bg, const void *pResource, u32 tileOffset, u32 palBank, u32 x, u32 y);
// Loads a graphic's tiles and palette without drawing its tilemap; returns the tilemap for sub_08006C00.
extern void *LoadBgGraphicTiles_candidate(u32 bg, const void *pResource, u32 tileOffset, u32 palBank);
// Draws a loaded graphic's tilemap (LoadBgGraphicTiles_candidate's result) on a BG at tile (x, y).
extern void WriteBgGraphicTilemap_candidate(u32 bg, const void *pTilemap, u32 tileOffset, u32 palBank, u32 x, u32 y);
extern void SetAlphaBlendTargets(u8 arg0, u32 arg1);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void sub_0800A914(void);
// One frame of a BG tile animation: its tile data and how many ticks it shows
// (0 holds it).
typedef struct BgTileAnimFrame {
    const void *pTiles;
    u32 dwDuration;
} BgTileAnimFrame;

// A BG tile animation registered by sub_0800A598 and stepped by
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
extern void sub_0803094C(u32 arg);
extern void sub_08001D90(u32 arg);

extern const u32 g_dwStartupBg3Control;
extern const u32 g_dwStartupBg2Control;
extern const u32 g_dwStartupBg1Control;
extern const u32 g_dwLanguageSelectBg3Control;
extern const u32 g_dwLanguageSelectBg2Control;
extern const u32 g_dwLanguageSelectBg1Control;

// Sets both current and target scroll (both axes snap instantly, no interpolation).
extern void SetBgScroll_candidate(u32 bg, s32 x, s32 y);
extern void sub_08007464(u32 bg, u16 tile);
extern void DrawLanguageSelectEntries_candidate(void);
extern void DrawLanguageSelectEntry_candidate(u32 index, u32 selectedIndex);
extern void DrawLanguageSelectPicture_candidate(u32 selectedIndex);
// The write-only half of SetBgControl: writes BGxCNT and the tilemap/charblock
// VRAM bases, without enabling the layer via SetDispcntFlag.
extern void SetBgControlRegister_candidate(u32 bg, u32 control);
// X-only counterpart of SetBgScroll; `position` is already 16.16 fixed-point.
extern void SetBgScrollX_candidate(u32 bg, s32 position);
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
