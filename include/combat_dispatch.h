#pragma once

#include "combat.h"
#include "video.h"

// bIndex/dwParam are adjacent globals (0x03002688/0x0300268C) accessed
// through one base address in the real code, hence one struct here.
typedef struct {
    u8 bIndex;    // sentinel 0xFF = none pending
    u8 bCountdown;  // set to 2 by sub_08013320; the pending copy runs when it wraps past 0
    u32 dwParam;
} BattleMessageIconState;

extern void InitCharacterSpells_candidate(u32 index, u16 *pStats);
extern void StopBgTileAnimationsAfterCard_candidate(void);  // stops all BG tile animations
extern void sub_08012A00(void);
extern void ClearBattleTextPanel(void);
extern void MoveEnemyTargetCursor(s32 step);
extern void MoveAllyTargetCursor(s32 step);
// Wait for scanline 42, then end the target flash started by FlashEnemyTarget and its siblings.
extern void StopEnemyTargetFlash(u32 slot);
extern void StopAllyTargetFlash(u32 slot);
extern void StopPendingFighterFlash(u32 pendingIndex);
extern void SelectBattleMenuIcon(u32 row);  // enlarges row's menu icon and shrinks the previous one
extern u32 WrapBattleMenuCursor(u32 cursor, u32 lastRow);
extern void DrawAllyTargetStats(u32 slot);
extern void DrawBattleMenuFrame(void);
extern void ClearBattleMessageLine(u8 line);
// Clears the battle message box and hides the battle menu icons.
extern void PrepareBattleMessageDisplay_candidate(void);
// The room's battle background graphic blob: the second entry of g_aBattleBackgroundPairs, or a
// fixed alternate blob for rooms 8-15 under one battle-state condition.
extern void *GetBattleBackgroundGraphic(void);
extern u8 *GetBattleBackgroundData_candidate(void);
extern void PushBattleState(s32 state);
extern void sub_08012B40(void);
extern void OpenEnemyTargetMenu_candidate(u8 fighterIndex);  // bMenuScreen 6, 0x08012B98
extern void HideBattleMenuIcon(u8 row);
extern s32 sub_08012E0C(u8 fighterIndex);  // 1 if the fighter has a shadow Actor (monsters 45-47)
extern void SetFighterTurnOrderIconDone(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its idle frame
extern void TogglePendingFighterCursor_candidate(void);
extern void sub_08013108(u8 fighterIndex);        // cursor/highlight-to-fighter
extern void OpenPendingFighterMenu_candidate(u8 fighterIndex);  // bMenuScreen 9, 0x0801319C

extern void IgnoreBattleMenuInput(u32 fighterType, BattleFighter *pFighter);  // does nothing; screens 0, 3 and 10
extern void ConfirmBattleTopMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpellChoiceMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpecialMoveMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpellTierMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmItemMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmAllyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmPendingFighterMenu_candidate(u32 fighterType, BattleFighter *pFighter);
extern void CancelBattleTopMenu(u32 fighterType, BattleFighter *pFighter);  // does nothing
// Reopens the top menu on the row that opened the current screen (spell, special move or item).
extern void CancelToBattleTopMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelSpellTierMenu(u32 fighterType, BattleFighter *pFighter);  // back to the spell choice menu
extern void CancelEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelAllyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelPendingFighterMenu_candidate(u32 fighterType, BattleFighter *pFighter);  // reopens the top menu on row 1

extern u32 g_dwSelectedBattleMenuIcon;  // row whose icon SelectBattleMenuIcon enlarged
// The row of battle menu icons along the bottom of the screen, one Actor per menu row.
extern Actor *g_apBattleMenuIconActors[7];
// Battle-message icon actor (shown alongside ShowBattleMessage's text).
extern Actor *g_pBattleMessageIconActor_candidate;
extern BattleMessageIconState g_BattleMessageIconState_candidate;
extern s32 g_anFaintedRosterIndices[4];
extern void SetupAllyBattleMessageIcon_candidate(u32 fighterType);
extern void SetupEnemyBattleMessageIcon_candidate(u32 monsterId);
// g_aBattleScanlineEffects with entry 1 moved to FightState.bWallEndLine.
extern ScanlineEffectEntry g_aBattleScanlineEffectBuffer[4];
