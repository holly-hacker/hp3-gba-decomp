#pragma once

#include "types.h"
#include "actor.h"
#include "battle/battle.h"
#include "battle/effect_script.h"
#include "battle/encounters.h"
#include "battle/monster_drop_table.h"
#include "constants/spells.h"
#include "video.h"

// Combat actors, damage, spells and effects.

extern void sub_0801493C(void);
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
extern Actor *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage);
extern Actor *CreateEffectScriptActor(s32 effectId, s32 kind);  // 0x08018BE0
extern void InterpretActorScript(Actor *actor);
extern ParticleEmitter *CreateBattleEffectEmitter_candidate(Actor *actor, s32 a1, s32 a2, s32 a3,
                                                             s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                                                             s32 a9, s32 a10, s32 a11, s32 a12, s32 a13,
                                                             s32 a14, s32 a15, s32 a16);
// Scanline callback of the effect tables.
extern void sub_0801B130(u32 *pPayload0, u32 *pPayload1);
extern ParticleEmitter *sub_0801B204(Actor *actor, u32 a, u32 b);
extern ParticleEmitter *sub_0801B2EC(Actor *actor, u32 a, u32 b);
extern ParticleEmitter *sub_0801B348(Actor *actor, u32 a, u32 b);
extern s32 TryApplyParalysis(BattleFighter *fighter, s32 isEnemyMonster, s32 escapeChance);
extern void sub_0801B4BC(u32 a, void *b, u32 c, u32 d, void *e);
extern void SpawnParalysisEffect(Actor *actor);

// Data tables.
extern const MonsterGfxRow g_pMonsterGraphicsTable[69];  // 0x0804E6B4, src/combat_2/monster_graphics_table.c
// Companion sprite InitMonsterBattleActor spawns for monsters 45-47.
extern const ActorAssetRecord g_MonsterShadowGfxRow;               // 0x0804EF54
extern const ActorAssetRecord g_aEnemyTurnOrderIconAssets[69];     // 0x0804EF64
extern const ActorAssetRecord g_aAllyTurnOrderIconAssets[4];       // 0x0804F3B4
extern const ActorAssetRecord g_TurnOrderIconContainerAsset;       // 0x0804F3F4
// Sound played when a party fighter takes damage, per FighterType: [0] for a light hit, [1] for more
// than a third of max HP damage (or 1000/1001); [2] has no reader found.
extern const u8 g_aabFighterHurtSoundIds[4][3];  // 0x0804F404
extern const MonsterTableRow MonsterTable[];  // 0x0804F410, src/combat_2/monsters.c
extern const u32 g_adwFolioBrutiMonsterScale[69];  // 0x0804FA88
extern const u8 g_aMonsterAttackOffset_candidate[69][2];  // 0x0804FB9C, [rosterIndex]
extern const MonsterDropEntry g_pMonsterDropTable[69];
extern const CharacterLevelEntry g_pHarryLevelTable[];     // 0x0804FE50, src/combat_2/harry_levels.c
extern const CharacterLevelEntry g_pRonLevelTable[];       // 0x08050300, src/combat_2/ron_levels.c
extern const CharacterLevelEntry g_pHermioneLevelTable[];  // 0x080507B0, src/combat_2/hermione_levels.c
extern const CharacterLevelEntry *const g_apCharacterLevelTables[3];  // 0x08050C60, Harry, Hermione, Ron
extern const RandomEncounter g_aRandomEncounters[30];
// One fight's four enemy slots; 255 (0xFF) = empty slot.
extern const u8 g_aScriptedEncounters[15][4];
extern const FighterAnimRow g_aFighterAnimTable[4];  // 0x08051248, src/combat_2/fighter_anim_table.c
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
extern const u32 g_adwEffectBgControlOverride_candidate[4];  // 0x080539A8
extern const ScanlineEffectEntry g_aEffectScanlineTable0[6];   // 0x080539B8
extern const ScanlineEffectEntry g_aEffectScanlineTable1[9];   // 0x08053A18
extern const ScanlineEffectEntry g_aEffectScanlineTable2[6];   // 0x08053AA8
extern const ScanlineEffectEntry *const g_apEffectScanlineTables_candidate[3];  // 0x08053B08
extern const u8 g_abEffectScanlineTableSizes_candidate[3];    // 0x08053B14
extern const EffectStreamList32 g_RainStreakList_candidate;  // 0x08053B18
extern const EffectStreamList8 g_RainSplashList_candidate;   // 0x08053C20
extern const ActorOrbit g_aEffectOrbitParams_candidate[16];  // 0x08053C68
extern const u8 g_abEffectRosterIdPair_candidate[2];         // 0x08053D28
extern const u16 g_awBattleSlotPosX_candidate[7];            // 0x08053D2A, per fighter slot
extern const u8 g_abBattleSlotPosY_candidate[7];             // 0x08053D38
extern const ActorAssetRecord g_aEffectActorAssets[17];    // 0x08053D40
extern void *const g_apEffectPalettes[5];                    // 0x08053E50
extern const ActorAssetRecord g_aEffectAnimAssets[65];      // 0x08053E64, opcodes 0x01/0x02
extern const ActorAssetRecord g_aEffectAnimAssets2[38];     // 0x08054274, opcodes 0x03/0x04
extern const EffectBgRecord g_aEffectBgRecords_candidate[166];  // 0x080544D4
extern const u8 g_abScriptOpcodeLengths[168];                // 0x08054F34, operand bytes per opcode
extern const u8 g_abFighterIdleAnimData_candidate[6];        // 0x08054FDC
extern const u8 g_aEffectAnimData_candidate[65][226];        // 0x08054FE2
extern const u8 g_aEffectAnimData2_candidate[38][108];       // 0x08058944
extern const u8 *const g_apEffectScripts[65];                // 0x0805B978, one script per effect id

extern u8 g_bDefeatWarpParam;
extern u8 g_bSpellMissStreak;
extern u16 g_nLastDamage;
extern u8 g_bLastTargetIndex;
extern EffectStaging g_effectStaging;
extern u8 g_bReviveInsertCount_candidate;
