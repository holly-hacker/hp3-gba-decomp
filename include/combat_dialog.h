#pragma once

#include "battle/battle.h"
#include "constants/spells.h"
#include "video.h"

extern void TickBattleMenuInput(void);
extern void OpenBattleTopMenu(s32 fighterIndex, s32 arg1);
extern void OpenAllyTargetMenu(u8 fighterIndex);             // bMenuScreen 8, 0x080107BC
extern void ShowBattleMessage(s32 code, s32 arg1, s32 arg2);

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
extern const ScanlineEffectEntry g_aBattleScanlineEffects[4];  // 0x0804E2AC

// TickBattleMenuInput calls the bMenuScreen entry of the confirm table on A and of the cancel
// table on B, passing the active fighter's FighterType and record.
typedef void (*BattleMenuInputHandler)(u32 fighterType, BattleFighter *pFighter);
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

