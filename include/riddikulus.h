#pragma once

#include "types.h"
#include "object.h"

// Riddikulus Boggart Challenge, game mode 0x2F (RiddikulusMinigame).

// The mode's screen state at 0x03002048, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    u8 abUnmapped_0[0x10];
    Object *pObject;         // 0x10; despawned when a round ends
    u32 dwUnk14;
    Object *pCursorObject;   // 0x18; released on exit when set
    void *pObjectGroup1C;    // 0x1C; freed on exit
    void *pObjectGroup20;    // 0x20; freed on exit
    s32 dwUnk24;
    u8 abUnmapped_28[4];
    u32 dwScore;             // 0x2C; compared against the saved high score
    s32 dwCountdown;         // 0x30; frames until the current state advances
    u8 bUnk34;
    u8 bUnk35;
    u8 abUnmapped_36[2];
    u32 dwExitToMenu;        // 0x38; 1 requests a return to the minigame menu
} RiddikulusState;

extern RiddikulusState g_Riddikulus;  // 0x03002048

// BG control words and the BG0 graphic.
extern const u32 g_dwRiddikulusBg0Control;  // 0x0804C1B0
extern const u32 g_dwRiddikulusBg3Control;  // 0x0804C1B4
extern const u8 g_RiddikulusBgGraphic[];    // 0x08E5B4AC

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    RiddikulusStateIntro = 0,
    RiddikulusStateAwaitInput = 1,
    RiddikulusStateInput = 2,
    RiddikulusStateResolve = 3,
    RiddikulusStateRoundEnd = 4,
    RiddikulusStateNextRound = 5,
    RiddikulusStateResultsMenu = 6,
    RiddikulusStatePauseMenu = 7,
} RiddikulusMode;

extern void sub_08008360(void);
extern void sub_08008404(void);
extern u32 sub_08008604(void);
extern void sub_08008698(void);
extern void sub_08008968(void);
extern void sub_08008A18(void);
extern void sub_08008B2C(u32 direction);
extern void sub_08008B84(void);
extern void sub_08008BD8(void);
extern void sub_08008C4C(void);
extern void sub_08008CA8(void);
extern void sub_08008D4C(void);
extern u32 sub_08008D80(void);
extern void sub_08008DFC(void);
extern void sub_08008E48(void);
