#pragma once

#include "types.h"
#include "actor.h"

// Combat result screen, game mode 0x2C (CombatResult), pushed by the battle state machine once the
// last enemy is defeated; see docs/memory-map/battle.md. It counts up the battle's XP, then
// shows the drops and gold. dwModeState values of UpdateCombatResult.
typedef enum {
    CombatResultStateXp = 0,         // XP counter, then "Press the A Button to continue."
    CombatResultStateFadeOutXp = 1,
    CombatResultStateFadeInDrops = 2,
    CombatResultStateDrops = 3,      // A returns to the overworld
    CombatResultStateDone = 4,
    CombatResultStateIntroDelay = 5, // counts dwModeTimer down to -1, then starts the XP phase
} CombatResultState;

// Source rectangle, in tiles, of a party member's portrait within the shared BG graphic.
typedef struct {
    u8 bSrcX;
    u8 bSrcY;
    u8 bWidth;
    u8 bHeight;
} CombatResultPortraitRect;

// Destination of a portrait on the screen, in tiles, per party position.
typedef struct {
    u8 bDstX;
    u8 bDstY;
    u8 abPad[2];
} CombatResultPortraitPosition;

extern const u32 g_dwCombatResultBg2Control;  // 0x0804E600
extern const u32 g_dwCombatResultBg1Control;  // 0x0804E604
extern const u32 g_dwCombatResultBg3Control;  // 0x0804E608
extern const u32 g_dwCombatResultBg0Control;  // 0x0804E60C

// Indexed by party stats slot (GetPartyMasterStatsSlot_candidate). The BG1 and BG2 graphics
// are cut up the same way, with their own destinations.
extern const CombatResultPortraitRect g_aCombatResultBg1PortraitRects[3];        // 0x0804E640
extern const CombatResultPortraitPosition g_aCombatResultBg1PortraitPositions[3];  // 0x0804E64C
extern const s8 g_abCombatResultPortraitScrollX[3];                         // 0x0804E658
extern const CombatResultPortraitRect g_aCombatResultBg2PortraitRects[3];        // 0x0804E65C
extern const CombatResultPortraitPosition g_aCombatResultBg2PortraitPositions[3];  // 0x0804E668

// Row of the XP phase's per-party-position display (left, right, centre), kept by
// InitializeCombatResultXp for TickCombatResultXpCounter. The tile cursors mark where each
// string's tiles start so that a tick can redraw it in place.
typedef struct {
    s32 nXpToNextLevel;       // mirrors the member's wRewardXp, clamped at 0 for display
    u16 wExpTileCursor;       // "Exp:" value
    u16 wLevelTileCursor;     // "Level:" value
    u16 wNextTileCursor;      // "Next:" value, unused from level 99
    u16 wLevelUpTileCursor;   // "Level Up!" text, reserved when the screen is set up
} CombatResultPartyRow;

// No item in a drop slot.
#define COMBAT_RESULT_NO_ITEM 0x85

extern const ActorAssetRecord g_CombatResultCoinAsset;          // 0x0804E610
extern const ActorAssetRecord g_CombatResultUnusedItemsAsset;   // 0x0804E620: no reader found
extern const ActorAssetRecord g_CombatResultLevelUpSparkleAsset;  // 0x0804E630
extern const u8 g_abCombatResultLevelUpSparkleAnim[];           // 0x0804E674
extern const u8 g_sCombatResultMacro1Space[];                   // 0x0804E6B0

extern u32 g_dwCombatResultUnusedCounter;  // 0x030026E8: zeroed by InitializeCombatResult, no reader found
extern u32 g_dwCombatResultUnusedDelay;    // 0x030026EC: 0x78 after InitializeCombatResult, no reader found
extern u32 g_dwCombatResultXpRemaining;  // 0x030026F0: counted down by TickCombatResultXpCounter
extern Actor *g_pCombatResultCoinActor;   // 0x030026F4
extern Actor *g_pCombatResultItem0Actor;  // 0x030026F8
extern Actor *g_pCombatResultItem1Actor;  // 0x030026FC
extern u8 g_abCombatResultPartySlots[3];  // 0x03002700: by party position, 3-member party: 1, 2, 0
extern const u16 *g_pCombatResultBg2Tilemap;   // 0x03002704
extern const u16 *g_pCombatResultBg1Tilemap;   // 0x03002708
extern u16 g_wCombatResultTextTileCursor;  // 0x0300270C
extern u16 g_wCombatResultXpTileCursor;    // 0x0300270E: start of the XP number's tiles
extern CombatResultPartyRow g_aCombatResultPartyRows[3];  // 0x03002710, by party position
extern u16 g_wCombatResultXpNumberX;       // 0x03002734: screen x of the XP number
extern ActorGfxRecord g_CombatResultItem0Gfx;  // 0x03002738: tile/frame data of the first drop's icon
extern ActorGfxRecord g_CombatResultItem1Gfx;  // 0x03002740: tile/frame data of the second drop's icon

extern void RollBattleItemDrops(int *pItemId0, int *pItemId1);  // 0x080147C0
extern void InitializeCombatResultXp(void);       // 0x08013AC8: draws the party's Exp/Level/Next rows
extern void TickCombatResultXpCounter(void);      // 0x08014004: one tick of the XP counter
extern void InitializeCombatResultDrops(void);    // 0x0801456C: rolls and lists the drops and the gold

