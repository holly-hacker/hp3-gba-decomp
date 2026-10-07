#pragma once

#include "types.h"

// Victory screen, game mode 0x2C (VictoryScreen), pushed by the battle state machine once the
// last enemy is defeated; see docs/memory-map/battle.md. It counts up the battle's XP, then
// shows the drops and gold. dwModeState values of UpdateVictoryScreen.
typedef enum {
    VictoryStateXp = 0,         // XP counter, then "Press the A Button to continue."
    VictoryStateFadeOutXp = 1,
    VictoryStateFadeInDrops = 2,
    VictoryStateDrops = 3,      // A returns to the overworld
    VictoryStateDone = 4,
    VictoryStateIntroDelay = 5, // counts dwModeTimer down to -1, then starts the XP phase
} VictoryState;

// Source rectangle, in tiles, of a party member's portrait within the shared BG graphic.
typedef struct {
    u8 bSrcX;
    u8 bSrcY;
    u8 bWidth;
    u8 bHeight;
} VictoryPortraitRect;

// Destination of a portrait on the screen, in tiles, per party position.
typedef struct {
    u8 bDstX;
    u8 bDstY;
    u8 abPad[2];
} VictoryPortraitPosition;

extern const u32 g_dwVictoryBg2Control;  // 0x0804E600
extern const u32 g_dwVictoryBg1Control;  // 0x0804E604
extern const u32 g_dwVictoryBg3Control;  // 0x0804E608
extern const u32 g_dwVictoryBg0Control;  // 0x0804E60C

// Indexed by party stats slot (GetPartyMasterStatsSlot_candidate). The BG1 and BG2 graphics
// are cut up the same way, with their own destinations.
extern const VictoryPortraitRect g_aVictoryBg1PortraitRects[3];        // 0x0804E640
extern const VictoryPortraitPosition g_aVictoryBg1PortraitPositions[3];  // 0x0804E64C
extern const s8 g_abVictoryPortraitScrollX[3];                         // 0x0804E658
extern const VictoryPortraitRect g_aVictoryBg2PortraitRects[3];        // 0x0804E65C
extern const VictoryPortraitPosition g_aVictoryBg2PortraitPositions[3];  // 0x0804E668

extern u32 g_dwVictoryUnk26E8;
extern u32 g_dwVictoryUnk26EC;
extern u32 g_dwVictoryXpRemaining;  // 0x030026F0: counted down by sub_08014004
extern u32 g_dwVictoryUnk26F4;
extern u32 g_dwVictoryUnk26F8;
extern u32 g_dwVictoryUnk26FC;
extern u8 g_abVictoryPartySlots[3];  // 0x03002700: by party position, 3-member party: 1, 2, 0
extern void *g_pVictoryBg2Tilemap;   // 0x03002704
extern void *g_pVictoryBg1Tilemap;   // 0x03002708
extern u16 g_wVictoryTextTileCursor;  // 0x0300270C
extern u16 g_wVictoryUnk2734;

extern void sub_08013AC8(void);
extern void sub_08014004(void);  // one tick of the XP counter, lowers g_dwVictoryXpRemaining
extern void sub_0801456C(void);  // starts the drop phase: rolls and lists the drops and the gold total
extern void sub_0801493C(void);
