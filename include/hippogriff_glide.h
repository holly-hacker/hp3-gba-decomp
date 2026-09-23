#pragma once

#include "types.h"

// Buckbeak's Hippogriff Glide, game mode 0x2B (HippogriffGlideMinigame).

// Allocated by InitializeHippogriffGlideMinigame, freed by
// ExitHippogriffGlideMinigame.
typedef struct {
    u8 abUnmapped_0[4];
    u32 dwScore;  // 0x04
    u8 abUnmapped_8[8];
    u32 dwUnk10;  // 0x10; cleared on init
    u8 abUnmapped_14[0x1DC];
} HippogriffGlideState;  // 0x1F0

extern HippogriffGlideState *g_pHippogriffGlide;  // 0x03002088

// Three words cleared on init; meaning not yet established.
extern u32 g_adwHippogriffGlideUnk[3];  // 0x03005D10

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    HippogriffGlideStateFlying = 0,   // Start opens the results menu
    HippogriffGlideStateResults = 1,
    HippogriffGlideStateExitSelect = 2,
    HippogriffGlideStateFinished = 3, // records the high score, reopens the results menu
} HippogriffGlideMode;

extern void ProcessHippogriffGlideMinigameFrame(void);
extern void InitializeHippogriffGlideResultsMenu(void);
extern void HandleHippogriffGlideResultsMenuSelect(void);
extern void HandleHippogriffGlideExitSelect(void);
extern void sub_0800907C(void);
extern void sub_08008E88(void);
extern void sub_0800975C(void);
extern void sub_08009D8C(void);
extern void sub_08009E1C(void);
