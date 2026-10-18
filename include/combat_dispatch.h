#pragma once

#include "battle/battle.h"

extern void InitCharacterSpells_candidate(u32 index, u16 *pStats);
extern void StopBgTileAnimationsAfterCard_candidate(void);  // stops all BG tile animations
extern void sub_08012A00(void);
extern void sub_08012A38(void);
// The room's battle background graphic blob: the second entry of g_aBattleBackgroundPairs, or a
// fixed alternate blob for rooms 8-15 under one battle-state condition.
extern void *GetBattleBackgroundGraphic(void);
extern u8 *GetBattleBackgroundData_candidate(void);
extern void PushBattleState(s32 state);
extern void sub_08012B40(void);
extern void OpenEnemyTargetMenu_candidate(u8 fighterIndex);  // bMenuScreen 6, 0x08012B98
extern void ClearFighterActorFlag_candidate(u8 fighterIndex);  // 0x08012CB4
extern s32 sub_08012E0C(u8 fighterIndex);  // 1 if the fighter has a shadow Actor (monsters 45-47)
extern void SetFighterTurnOrderIconDone(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its idle frame
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

extern u32 g_bSelectedFighterSlot_candidate;
// One slot per active BattleFighter -- see docs/formats/battle-ui.md.
extern Actor *g_apFighterActors_candidate[7];
// Battle-message icon actor (shown alongside ShowBattleMessage's text),
// distinct from the 7 per-fighter Actors in g_apFighterActors_candidate.
extern Actor *g_pBattleMessageIconActor_candidate;
extern BattleMessageIconState g_BattleMessageIconState_candidate;
extern s32 g_anFaintedRosterIndices[4];
