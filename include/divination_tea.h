#pragma once

#include "types.h"
#include "object.h"

// Tea Leaf Divination, game mode 0x1C (DivinationTeaMinigame).

#define DIVINATION_TEA_LEAF_COUNT 16

// One tea leaf object. Its affine scale words are fixed-point with 8
// fractional bits; wAngle is a 16-bit angle advanced every frame.
typedef struct {
    Object *pObject;  // 0x00
    u8 abUnmapped_4[0xC];
    s16 wScaleX;      // 0x10
    s16 wScaleY;      // 0x12
    s16 wAngle;       // 0x14
    u8 abUnmapped_16[2];
} DivinationTeaLeaf;  // 0x18

// The mode's screen state at 0x03005B28, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    DivinationTeaLeaf aLeaves[DIVINATION_TEA_LEAF_COUNT];  // 0x000
    Object *apCupObjects[4];   // 0x180; switched to a new animation when B is pressed
    Object *apFadeObjects[8];  // 0x190; affine flag bits cleared once the fade-in ends
    u32 dwBlendEvb;            // 0x1B0
    u32 dwBlendEva;            // 0x1B4
    u32 dwFadeStep;            // 0x1B8; 0..0x10, advanced by 2 per frame while fading
    u32 dwFrame;               // 0x1BC; frames since the mode started
    u32 dwUnk1C0;              // 0x1C0; set once B has been pressed
    u32 dwUnk1C4;
    const u8 *pFortuneText;    // 0x1C8; dialog text 0xA5F + random 0..0x5A
    u32 dwFortuneTextCursor;   // 0x1CC; PrintTextBox result for pFortuneText
    u32 dwUnk1D0;              // 0x1D0; starts at 0x40
    u32 dwUnk1D4;              // 0x1D4; dwFrame at the last A press
    u32 dwUnk1D8;              // 0x1D8; nonzero routes the update to sub_080422D0
    Object *pCursorObject;     // 0x1DC; released on exit when set
} DivinationTeaState;          // 0x1E0

extern DivinationTeaState g_DivinationTea;  // 0x03005B28

// BG control words for BG2, BG0 and BG1, the BG2/BG1 graphics, and animation
// data shared by the cup objects.
extern const u32 g_dwDivinationTeaBg2Control;  // 0x0806BB44
extern const u32 g_dwDivinationTeaBg0Control;  // 0x0806BB48
extern const u32 g_dwDivinationTeaBg1Control;  // 0x0806BB4C
extern const u8 g_DivinationTeaBg2Graphic[];   // 0x08E3849C
extern const u8 g_DivinationTeaBg1Graphic[];   // 0x08E39AA4
extern const u8 g_DivinationTeaCupAnimA[];     // 0x0806BB58
extern const u8 g_DivinationTeaCupAnimB[];     // 0x0806BB00
extern const u8 g_DivinationTeaTable[];        // 0x0806BB70

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    DivinationTeaStateIntro = 0,
    DivinationTeaStateFadeIn = 1,
    DivinationTeaStateReveal = 2,
    DivinationTeaStateFadeText = 3,
    DivinationTeaStateShowFortune = 4,
} DivinationTeaMode;

extern void sub_08007C2C(u32 bg, u32 arg1, u32 arg2);
extern void sub_08007CB4(u32 bg, u32 arg1, u32 arg2);
extern void sub_08007CD4(u32 bg, u32 arg1);
extern void sub_08041D84(void);
extern void sub_08041FA0(void);
extern void sub_0804200C(void);
extern void sub_080421B8(void);
extern void sub_08042288(u32 arg);
extern void sub_080422D0(void);
