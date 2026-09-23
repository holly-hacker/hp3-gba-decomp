#pragma once

#include "types.h"
#include "object.h"

// The mode's screen state at 0x03003A84. Only the fields the mode handlers use are named.
typedef struct {
    u8 abUnk00[0x88];
    u32 bParallaxScroll;  // 0x88: nonzero scrolls BGs 1-3 at different speeds, otherwise only the camera y
    Object *apPanelObject[8];  // 0x8C: one object per 32 pixels of screen width
    Object *pPanelObject8;     // 0xAC: placed at x = 0
    u8 abUnkB0[4];
    s32 nPanelOffset;     // 0xB4: panel's y offset from its resting position (0 = raised, 0x28 = lowered)
} LupinPotionCutsceneState;

extern LupinPotionCutsceneState g_LupinPotionCutscene;  // 0x03003A84
extern s32 g_aLupinPotionBg2Scroll[2];                  // 0x03003B3C

extern const u32 g_dwLupinPotionTextBgControl;  // 0x08062A30
extern const u8 g_aLupinPotionScanlineTable[];  // 0x08062A08: 2 scanline effect entries
extern const u8 g_LupinPotionEmbeddedPalette[]; // 0x08DC7A90

extern void sub_08028AD4(void);
extern void sub_08028F7C(void);
extern void sub_08028FD8(void);
extern void sub_08029144(void);
extern u32 sub_08029260(void);
extern void sub_08029380(void);
extern void sub_08029558(void);
