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
extern void PlayScreenTransitionInByIndex_candidate(u32 index, u32 arg);
extern void PlayScreenTransitionOutByIndex_candidate(s32 arg0, s32 arg1);

// ORs into / clears DISPCNT bits.
extern void SetDispcntFlag(u32 flags);
// Writes BGxCNT for BG `bg` and enables the layer.
extern void SetBgControl_candidate(u32 bg, u32 control);
extern void EnableBg(u32 bg);
extern void DisableBg(u32 bg);
extern void SetBgPriority(u32 bg, u32 priority);
extern void SetAlphaBlendCoefficients(u32 eva, u32 evb);

// Hardware windows: layer masks, rectangle (16.16 coordinates), and hiding one.
extern void SetScreenWindowLayers_candidate(u32 windowId, u32 winIn, u32 winOut);
extern void SetScreenWindowRect_candidate(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);
extern void HideScreenWindow_candidate(u32 windowId);

extern void sub_080073BC(u32 arg);
extern void sub_0803D338(u8 arg0, u32 arg1);
extern void sub_0803DA4C(u32 arg);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void sub_0800A03C(u32 arg);
extern void sub_0800A914(void);
extern void sub_0803094C(u32 arg);
extern void sub_08001D90(u32 arg);
