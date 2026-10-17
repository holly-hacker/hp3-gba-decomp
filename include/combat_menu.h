#pragma once

#include "types.h"
#include "actor.h"
#include "battle/battle.h"
#include "constants/spells.h"
#include "graphics/scanline_effects.h"

extern void DrawFighterStatsUi_candidate(s32 fighterType, s32 panelSlot);
extern void DrawEnemyStatsUi_candidate(s32 fighterIndex, s32 panelSlot);
extern void JitterEnemyTurnOrder(void);
extern void BuildTurnOrder(void);
extern void ReviveFighter_candidate(u8 pendingIdx);
extern void ClearParalyzedFighter_candidate(u8 fighterIndex);
extern void ClearPoisonedFighter_candidate(u8 fighterIndex);  // clears Poisoned, zeroes bPoisonDamage; CurePoison's shared helper
extern void InitBattleBackground_candidate(void);
extern void SetupBattleRoster(void);
extern void RestoreFighterActors_candidate(void);
extern void ResumeBattleAfterSubmode_candidate(void);
extern void TickBattleTurnStateMachine(void);
extern void SetFighterTurnOrderIconActive(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its highlighted frame, bringing it to the front
extern u8 RollFighterParalysisEscape(u8 fighterIndex);  // 0 = acts normally, 1 = still paralyzed, 3 = escape roll succeeded
extern void TrackSpellFamiliarity(u8 fighterType, u8 spellId, u8 spellLevel, u16 *pHp);  // 0x08010008
extern void DispatchPendingAction(s32 fighterIndex);
extern void TickBattleMenuInput(void);
extern void OpenBattleTopMenu(s32 fighterIndex, s32 arg1);
extern void OpenAllyTargetMenu(u8 fighterIndex);             // bMenuScreen 8, 0x080107BC
extern void ShowBattleMessage(s32 code, s32 arg1, s32 arg2);
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

extern const ActorAssetRecord g_BattleEffect001Asset;  // 0x0804D7F8, passed to sub_08030A1C by InitBattleBackground_candidate
// Label of each battle top menu row (Cast Spell, Special Move, Informus, Use Item, Flee,
// Folio Bruti, Help).
extern const u32 g_adwBattleTopMenuTextIds[7];  // 0x0804D808
// Records 0-71 are the attacking fighter portraits, 72-132 the battle-menu action icons.
extern const ActorAssetRecord g_aBattleHudAssets[133];  // 0x0804D824

extern const u32 g_dwBattleFloorBgControl;  // 0x0804E074, passed to InitFloorDisplay
extern const u32 g_dwBattleBg1Control;      // 0x0804E078
extern const u32 g_dwBattleBg0Control;      // 0x0804E07C, also the battle text target
extern const u32 g_dwBattleBgControlUnused_candidate;  // 0x0804E080, no reader found
// Spell id of each spell menu row, per party FighterType (Harry, Hermione, Ron).
extern const u8 g_aabFighterSpellMenu[3][7];  // 0x0804E084

typedef struct {
    const void *pFloor;  // graphic blob, see docs/formats/graphic_blob.md
    const void *pWall;
} BattleBackgroundPair;
extern const BattleBackgroundPair g_aBattleBackgroundPairs[55];  // 0x0804E09C, indexed by g_bCurrentRoomId

extern const u8 g_abBattleMusicByRoom[55];          // 0x0804E254, indexed by g_bCurrentRoomId
extern const u8 g_abBattleMusicByScriptedEncounter[15]; // 0x0804E28B, indexed by dwCurrentGameModeArg1 (scripted encounter id)

extern const ActorAssetRecord g_MenuSprite003Asset_candidate;  // 0x0804E29C, no reader found

// Battle screen scanline callbacks, copied to 0x03002690 by InitBattleBackground_candidate,
// sub_08012A00 and sub_08012B40.
extern void sub_08013360(u32 *pPayload0, u32 *pPayload1);
extern void sub_080133AC(u32 *pPayload0, u32 *pPayload1);
extern void sub_08013424(u32 *pPayload0, u32 *pPayload1);
extern const ScanlineEffectEntry g_aBattleScanlineEffects[4];  // 0x0804E2AC

// TickBattleMenuInput calls the bMenuScreen entry of the confirm table on A and of the cancel
// table on B, passing the active fighter's FighterType and record.
typedef void (*BattleMenuInputHandler)(u32 fighterType, BattleFighter *pFighter);
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
extern const BattleMenuInputHandler g_apfnBattleMenuConfirmHandlers[11];  // 0x0804E2EC
extern const BattleMenuInputHandler g_apfnBattleMenuCancelHandlers[11];   // 0x0804E318

// Battle message text ids. The per-fighter tables hold the four party FighterTypes, then the
// 69 monsters from index 4.
extern const u32 g_adwFighterActionTextIds[73];      // 0x0804E344, "Harry casts a spell:", "... attacks!"
extern const u32 g_adwFighterFaintTextIds[73];       // 0x0804E468, "... falls unconscious!", "... goes away!"
extern const u32 g_adwSpecialMoveResultTextIds[16];  // 0x0804E58C, by ShowBattleMessage's variant
extern const u32 g_adwReviveTextIds[5];              // 0x0804E5CC, by FighterType; 4 = the whole party

extern const u8 g_abSpellMaxLevel[SPELL_COUNT];  // 0x0804E5E0, by spell id; caps TrackSpellFamiliarity
extern const u32 g_adwFighterCantMoveTextIds[4];  // 0x0804E5EC, by party FighterType
extern const u8 g_sBattleTextSpace[];             // 0x0804E5FC, " "
