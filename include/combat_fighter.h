#pragma once

#include "types.h"
#include "actor.h"
#include "battle/battle.h"
#include "battle/encounters.h"
#include "battle/monster_drop_table.h"
#include "constants/spells.h"

// Battle actors, stats, actions and damage.

extern void ResetCharacterToLevel(u32 character, u32 level);  // sets a party member's saved level and stats from the level table
extern Actor *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex);
extern Actor *InitMonsterBattleActor(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex);
extern Actor *SpawnTurnOrderIcon(u32 rosterIndexOrFighterType, u32 isAlly, u32 turnOrderIndex, u32 gfxSlot);
extern void RollMonsterSpecialEffect(s32 monsterIndex, s32 targetFighterIndex, s32 damage);
extern void RecomputeBaseStatsFromLevel_candidate(u32 character);
// Experience helpers, by party stats slot.
extern s32 GetPartyMemberTotalXp(u32 slot);        // XP earned so far, 0x08015110
extern void LevelUpPartyMember_candidate(u32 fighterType);
extern void InitPartyStatForCurrentLevel(u32 index);
extern u16 sub_080152CC(s32 x, s32 fighterIndex);
extern u16 sub_08015334(s32 x, s32 fighterIndex);
extern void SetMonsterActorAnim(Actor *actor, u8 state);  // 0x0801539C, monster gfx tables + shadow
extern void SetPlayerActorAnim(Actor *actor, s32 state);   // 0x08015484, party fighter anim tables
extern void UpdateFighterFlashEffect_candidate(Actor *actor);  // 0x08015574
extern void TickFighterAttackAnimState_candidate(Actor *actor);  // 0x08015608
extern void ShowItemUseResult(Actor *actor, s32 targetIndex);
extern void TickPlayerActionState(Actor *actor);
extern void ShowDamageNumber_candidate(s32 targetIndex, s32 damage);
extern s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex);
extern s32 ResolveEnemyAttack(s32 attackerIndex, s32 defenderIndex);
extern void ApplyDamageToEnemyFighter(s32 damage, s32 fighterIndex);  // 0x08017F98
extern void ApplyDamageToAllyFighter(s32 damage, s32 fighterIndex);
extern void ShowFloatingDamageNumber_candidate(s32 damage, s32 code, s32 fighterIndex, s32 flag);
extern void CheckBattleDefeat(void);
extern void PruneFaintedAndRebuildTurnOrder_candidate(s32 arg0);
extern void CheckBattleVictory(Actor *actor);                  // 0x080186E0
extern void ResetAllPartyLevelsTo1(void);
extern void ResetPartyHpMpAndStats(void);
void DeserializePartyStats(void);
void SerializePartyStats(void);
extern s32 GetPartyMemberXpToNextLevel(u32 slot);  // XP still needed for the next level, 0x08018858
// The spell's effectiveness (0-100) against a monster, or -1 for a spell the monster has no entry for.
extern s32 GetMonsterSpellEffectiveness(s32 monsterIndex, s32 spellIndex);
extern s32 sub_080189C8(u32 rosterIndex);  // per-monster XP reward
extern s32 sub_08018AB8(u32 rosterIndex);  // per-monster gold reward
extern void PostActionBattleCheck(void);
extern void sub_08018B14(u16 damage, s32 fighterIndex);

// Data tables.
extern const MonsterGfxRow g_pMonsterGraphicsTable[69];  // 0x0804E6B4, src/combat_fighter/monster_graphics_table.c
// Companion sprite InitMonsterBattleActor spawns for monsters 45-47.
extern const ActorAssetRecord g_MonsterShadowGfxRow;               // 0x0804EF54
extern const ActorAssetRecord g_aEnemyTurnOrderIconAssets[69];     // 0x0804EF64
extern const ActorAssetRecord g_aAllyTurnOrderIconAssets[4];       // 0x0804F3B4
extern const ActorAssetRecord g_TurnOrderIconContainerAsset;       // 0x0804F3F4
// Sound played when a party fighter takes damage, per FighterType: [0] for a light hit, [1] for more
// than a third of max HP damage (or 1000/1001); [2] has no reader found.
extern const u8 g_aabFighterHurtSoundIds[4][3];  // 0x0804F404
extern const MonsterTableRow MonsterTable[];  // 0x0804F410, src/combat_fighter/monsters.c
extern const u32 g_adwFolioBrutiMonsterScale[69];  // 0x0804FA88
extern const u8 g_aMonsterAttackOffset_candidate[69][2];  // 0x0804FB9C, [rosterIndex]
extern const MonsterDropEntry g_pMonsterDropTable[69];
extern const CharacterLevelEntry g_pHarryLevelTable[];     // 0x0804FE50, src/combat_fighter/harry_levels.c
extern const CharacterLevelEntry g_pRonLevelTable[];       // 0x08050300, src/combat_fighter/ron_levels.c
extern const CharacterLevelEntry g_pHermioneLevelTable[];  // 0x080507B0, src/combat_fighter/hermione_levels.c
extern const CharacterLevelEntry *const g_apCharacterLevelTables[3];  // 0x08050C60, Harry, Hermione, Ron
extern const RandomEncounter g_aRandomEncounters[30];
// One fight's four enemy slots; 255 (0xFF) = empty slot.
extern const u8 g_aScriptedEncounters[15][4];
extern const FighterAnimRow g_aFighterAnimTable[4];  // 0x08051248, src/combat_fighter/fighter_anim_table.c
extern const u8 g_abHarryCardEffectId[22];      // 0x080514C8
extern const u8 g_aCardTargetingMeta[22][2];     // 0x080514DE
extern const u8 g_abSpecialMoveEffectId[3];      // 0x0805150A
extern const u8 g_abHermioneLectureEffectId[3];  // 0x0805150D
extern const u32 g_aDefeatWarpRoomId[20];       // 0x08051510
extern const u8 g_aFighterAnimDataTable[4][10][58];  // 0x08051560, [fighter][anim state]
extern const u8 g_pMonsterAnimFrameTable[69][96];  // 0x08051E70
extern const u8 g_MonsterShadowAnimData[96];     // 0x08053850
extern const u8 g_abSpellEffectScriptId[10][3];  // 0x080538B0, [spellId][level]
extern const u8 g_abSpellUnknownByLevel[10][3];  // 0x080538CE, [spellId][level], no known reader
extern const u16 g_awSpellPowerBase[SPELL_COUNT][SPELL_LEVELS];
extern const u16 g_awSpellPowerScale[SPELL_COUNT][SPELL_LEVELS];
extern const u16 g_awSpellMpCost[SPELL_COUNT][SPELL_LEVELS];  // 0x08053964
// Screen anchor an attacker walks to, per target's BattleFighter.bSlotParam,
// as {x, y} in whole pixels; the monster's own {x, y} extent in
// g_aMonsterAttackOffset_candidate is subtracted off to get the destination.
extern const u8 g_aBattleSlotAnchorPos_candidate[3][2];  // 0x080539A0, [bSlotParam]

extern u8 g_bInformusTargetMonster;  // monster id Informus last targeted, passed to the Folio Bruti
extern u8 g_bSpellMissStreak;
extern u16 g_nLastDamage;
extern u8 g_bLastTargetIndex;
