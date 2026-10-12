#pragma once

#include "types.h"

extern u32 g_dwBuckbeakMinigameForceOverworldExit;  // 0x03002084; set by StartMinigame

// Buckbeak's Hippogriff Glide, game mode 0x2B (BuckbeakMinigame).

// Allocated by InitializeBuckbeakMinigame, freed by
// ExitBuckbeakMinigame.
typedef struct {
    u8 abUnmapped_0[4];
    u32 dwScore;  // 0x04
    u8 abUnmapped_8[8];
    u32 dwUnk10;  // 0x10; cleared on init
    u8 abUnmapped_14[0x1DC];
} BuckbeakMinigameState;  // 0x1F0

extern BuckbeakMinigameState *g_pBuckbeakMinigame;  // 0x03002088

// Three words cleared on init; meaning not yet established.
extern u32 g_adwBuckbeakMinigameUnk[3];  // 0x03005D10

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    BuckbeakMinigameStateFlying = 0,   // Start opens the results menu
    BuckbeakMinigameStateResults = 1,
    BuckbeakMinigameStateExitSelect = 2,
    BuckbeakMinigameStateFinished = 3, // records the high score, reopens the results menu
} BuckbeakMinigameMode;

extern void ProcessBuckbeakMinigameFrame(void);
extern void InitializeBuckbeakMinigameResultsMenu(void);
extern void HandleBuckbeakMinigameResultsMenuSelect(void);
extern void HandleBuckbeakMinigameExitSelect(void);
extern void sub_0800907C(void);
extern void sub_08008E88(void);
extern void sub_0800975C(void);
extern void sub_08009D8C(void);
extern void sub_08009E1C(void);
