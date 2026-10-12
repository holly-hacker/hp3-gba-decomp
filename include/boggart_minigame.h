#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/minigames/boggart.h"

extern u32 g_dwBoggartMinigameScriptFlag_candidate;  // 0x03002040; set by StartMinigame

// Riddikulus Boggart Challenge, game mode 0x2F (BoggartMinigame).

// The mode's screen state at 0x03002048, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    u8 abUnmapped_0[0x10];
    Actor *pActor;         // 0x10; despawned when a round ends
    u32 dwUnk14;
    Actor *pCursorActor;   // 0x18; released on exit when set
    void *pActorGroup1C;    // 0x1C; freed on exit
    void *pActorGroup20;    // 0x20; freed on exit
    s32 dwUnk24;
    u8 abUnmapped_28[4];
    u32 dwScore;             // 0x2C; compared against the saved high score
    s32 dwCountdown;         // 0x30; frames until the current state advances
    u8 bUnk34;
    u8 bUnk35;
    u8 abUnmapped_36[2];
    u32 dwExitToMenu;        // 0x38; 1 requests a return to the minigame menu
} BoggartMinigameState;

extern BoggartMinigameState g_BoggartMinigame;  // 0x03002048

// BG control words and the BG0 graphic.
extern const u32 g_dwBoggartMinigameBg0Control;  // 0x0804C1B0
extern const u32 g_dwBoggartMinigameBg3Control;  // 0x0804C1B4

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    BoggartMinigameStateIntro = 0,
    BoggartMinigameStateAwaitInput = 1,
    BoggartMinigameStateInput = 2,
    BoggartMinigameStateResolve = 3,
    BoggartMinigameStateRoundEnd = 4,
    BoggartMinigameStateNextRound = 5,
    BoggartMinigameStateResultsMenu = 6,
    BoggartMinigameStatePauseMenu = 7,
} BoggartMinigameMode;

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
