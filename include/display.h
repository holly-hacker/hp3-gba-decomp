#pragma once

#include "types.h"

// Display registers and BG layers. sub_ names are still unidentified.

extern void ClearVram(void);
extern void ClearPaletteRam(void);

// Per-frame ticks run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickBgLayers_candidate(void);
extern void TickScreenWindows_candidate(void);
extern void TickPaletteAnimations_candidate(void);
extern void TickBgTileAnimations_candidate(void);

extern u32 g_aBgScrollState[];  // 0x03001E80; [0x25] == 0x03001F14
extern u8 g_abBgPriority[];     // 0x03003F8C; [4] == 0x03003F90

extern void sub_0800D264(void *ptr, s16 val1, s16 val2);  // 25-entry palette-flash/fade queue; val1/val2 real width is 16-bit
extern void sub_0800D254(void *ptr, s16 val1, s16 val2);
extern void LoadEmbeddedPalette_candidate(u8 *blob, s32 paletteRowOffset, s32 rowCount);
// Dispatches through the 4-entry handler table at 0x0806B844 by transitionIndex.
extern void PlayScreenTransitionInByIndex(u32 blendArg, u32 transitionIndex);
// Dispatches through the parallel handler table at 0x0806B880 by transitionIndex.
extern void PlayScreenTransitionOutByIndex(u32 blendArg, u32 transitionIndex);

// ORs into / clears DISPCNT bits.
extern void SetDispcntFlag(u32 flags);
// Writes BGxCNT for BG `bg` and enables the layer.
extern void SetBgControl(u32 bg, u32 control);
extern void EnableBg(u32 bg);
extern void DisableBg(u32 bg);
extern void SetBgPriority(u32 bg, u32 priority);
extern void SetAlphaBlendCoefficients(u16 eva, u16 evb);

// Hardware windows: layer masks, rectangle (16.16 coordinates), and hiding one.
extern void SetScreenWindowLayers_candidate(u32 windowId, u32 winIn, u32 winOut);
extern void SetScreenWindowRect_candidate(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);
extern void HideScreenWindow_candidate(u32 windowId);

extern void ResetDisplayState(u32 arg);
extern void ClearBgTilemap(u32 bg);
extern void *LoadBgGraphic(u32 bg, const void *pResource, u32 tileOffset, u32 palBank, u32 x, u32 y);
extern void SetAlphaBlendTargets(u8 arg0, u32 arg1);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void sub_0800A914(void);
extern void sub_0803094C(u32 arg);
extern void sub_08001D90(u32 arg);

extern const u32 g_dwStartupBg3Control;
extern const u32 g_dwStartupBg2Control;
extern const u32 g_dwStartupBg1Control;
extern const u8 g_StartupBg3Graphic[];
extern const u8 g_StartupBg2Graphic[];
extern const u8 g_StartupNoticeGraphic[];
extern const u32 g_dwLanguageSelectBg3Control;
extern const u32 g_dwLanguageSelectBg2Control;
extern const u32 g_dwLanguageSelectBg1Control;
extern const u8 g_MenuBg3Graphic[];
extern const u8 g_LanguageSelectBg2Graphic[];
extern const u8 g_LanguageSelectBg1Graphic[];

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
extern void sub_0803D420(u32 arg0, u32 arg1);
