#pragma once

#include "types.h"
#include "actor.h"
#include "battle/battle.h"
#include "battle/effect_script.h"

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
