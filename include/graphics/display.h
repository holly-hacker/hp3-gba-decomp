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
extern void TickBgTileAnimations_candidate(void);

// Per-BG scroll/affine state, 0x6C bytes per BG starting at g_aBgScrollState.
typedef struct BgScrollState {
    u8 pad_00[0x1C];
    u32 dwFlags;                 // 0x1C, bit 0x8000 asks for a scroll update
    u8 pad_20[0x08];
    u32 nScrollY_candidate;      // 0x28, 16.16
    u8 pad_2C[0x40];
} BgScrollState;
extern BgScrollState g_aBgScrollState[];  // 0x03001E80; [1].nScrollY_candidate == 0x03001F14
extern u8 g_abBgPriority[];     // 0x03003F8C; [4] == 0x03003F90

extern void sub_0800D264(void *ptr, s16 val1, s16 val2);  // 25-entry palette-flash/fade queue; val1/val2 real width is 16-bit
extern void sub_0800D254(void *ptr, s16 val1, s16 val2);
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
extern void SetBgPriority(u32 bg, u32 priority);
extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);
// Sets BLDCNT (layer mask | fade mode) and BLDY (amount, at most 0x10).
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void SetFadeToBlack(u16 layerMask, u16 amount);

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
// TickBgTileAnimations_candidate; see docs/memory-map/frame_systems.md.
#define BG_TILE_ANIMATION(frameCount) struct {                       \
    u8 bFlags;                                                        \
    u8 bFrameCount;                                                   \
    u16 wUnk2;            /* copied into the animation's entry */     \
    u32 dwBufferSize;     /* bytes allocated for the decoded tiles */ \
    BgTileAnimFrame aFrames[frameCount];                              \
}

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
