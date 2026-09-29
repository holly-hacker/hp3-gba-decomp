#pragma once

#include "types.h"

// State of the Harry Patronus cutscene: two affine BGs (2 and 3) that alternate showing the
// next of six graphics; the VBlank callback applies the scroll values and the layer swap.
extern u32 g_dwPatronusBgFront;      // 0x030051E4: BG currently shown
extern u32 g_dwPatronusBgBack;       // 0x030051E8: BG the next graphic is loaded into
extern u32 g_dwPatronusSwapPending;  // 0x030051EC: set when the VBlank callback should swap the BGs
extern u8 g_bPatronusGraphicIndex;   // 0x030051F0: cycles through g_apPatronusGraphics
extern s16 g_swPatronusBgParam;      // 0x030051F2: sub_08007CF4 argument, starts 0x180 then 0x200
extern s32 g_nPatronusBgOffset;      // 0x030051F4: 16.16; sub_08007C94 gets the integer part

extern const u32 g_dwPatronusBg2Control;             // 0x08068C30
extern const u32 g_dwPatronusBg3Control;             // 0x08068C34
extern const u8 *const g_apPatronusGraphics[6];      // 0x08FAAEF8

extern void HandleHarryPatronusCutsceneVBlank(void);
