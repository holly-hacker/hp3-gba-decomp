#pragma once

#include "combat.h"
#include "constants/spells.h"

// Battle actors, stats, actions and damage.

// One MonsterTable record, 0x18 bytes.
typedef struct MonsterTableRow {
    u16 wHp;                 // 0x00
    u8 bLevel;               // 0x02
    u8 bAgility;             // 0x03
    u8 bAccuracy;            // 0x04
    u8 bCritChance;          // 0x05
    u16 wDamageMin;          // 0x06
    u16 wDamageMax;          // 0x08
    u8 abEffectiveness[6];   // 0x0A
    u16 wRewardXp;           // 0x10
    u16 wRewardGold;         // 0x12
    u8 bSpecialChance;       // 0x14, not copied to BattleFighter
    u8 bSpecialId;           // 0x15, not copied to BattleFighter
    u16 wUnused;             // 0x16, zero in every row
} MonsterTableRow;

// One per-level row of Harry/Ron/Hermione's level-up stat tables, 12 bytes
// (last 2 always zero, not a real field), indexed by the saved 0-based
// bLevel (displayed level N is row N-1). wXpDeltaForLevel is the XP from
// that level to the next. bDefenseFactorPercent and bMagicDefensePercent are
// dead: RecomputeBaseStatsFromLevel resets both to 100 right after
// LevelUpPartyMember applies them.
typedef struct CharacterLevelEntry {
    u16 wHp_max;
    u16 wMp_max;
    u16 wXpDeltaForLevel;
    u8 bAgility;
    u8 bAccuracy;
    u8 bDefenseFactorPercent;
    u8 bMagicDefensePercent;
} CharacterLevelEntry;

// One row per MonsterTable entry.
typedef struct MonsterGfxRow {
    ActorAssetRecord battle;     // 0x00, battle and Folio Bruti sprite
    ActorAssetRecord overworld;  // 0x10, wandering-monster sprite
} MonsterGfxRow;

// per-wActorType windup-flash resource pointer row, stride 0xA0
// One row per FighterType: sprite records selected by animation state
// (SetPlayerActorAnim). Record 0 is the live sprite, 6 and 7 carry the
// windup flash palettes, 8 is the fainted sprite.
typedef struct FighterAnimRow {
    ActorAssetRecord aRecords[10];
} FighterAnimRow;

// One random-encounter id's 3 kinds x 4 random variants of enemy slots.
// At spawn time one variant is picked with Mt19937RandMax(3) and stored
// on the wandering-monster actor; touching it starts a battle with
// exactly that cell as the enemy roster. Each variant is 4 monster ids,
// one per enemy slot; 255 (0xFF) = empty slot (see SetupBattleRoster).
typedef struct {
    u8 aVariants[4][4];
} RandomEncounterKind;

typedef struct {
    RandomEncounterKind aKinds[3];
} RandomEncounter;

typedef struct {
    u8 chance;
    s16 itemId;
} MonsterDropSlot;

typedef struct {
    MonsterDropSlot slot[2];
} MonsterDropEntry;

// The three salamanders (Salamander, Amazonian Salamander, Peruvian
// Salamander) are the monsters with a companion shadow Actor.
#define IS_SALAMANDER(monster) ((monster) == 45 || (monster) == 46 || (monster) == 47)

extern void ResetCharacterToLevel(u32 character, u32 level);
extern Actor *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex);
extern Actor *InitMonsterBattleActor(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex);
extern Actor *SpawnTurnOrderIcon(u32 rosterIndexOrFighterType, u32 isAlly, u32 turnOrderIndex, u32 gfxSlot);
extern void RollMonsterSpecialEffect(s32 monsterIndex, s32 targetFighterIndex, s32 damage);
extern void RecomputeBaseStatsFromLevel(u32 character);
extern s32 GetPartyMemberTotalXp(u32 slot);
extern void LevelUpPartyMember(u32 fighterType);
extern void InitPartyStatForCurrentLevel(u32 index);
extern s32 RestoreFighterHp(s32 amount, s32 fighterIndex);
extern s32 RestoreFighterMp(s32 amount, s32 fighterIndex);
extern void SetMonsterActorAnim(Actor *actor, u8 state);  // 0x0801539C, monster gfx tables + shadow
extern void SetPlayerActorAnim(Actor *actor, s32 state);   // 0x08015484, party fighter anim tables
extern void UpdateMonsterScreenShake(Actor *actor);
extern void TickFighterAttackAnimState_candidate(Actor *actor);  // 0x08015608
extern void ShowAttackResult(Actor *actor, s32 targetIndex);
extern void TickPlayerActionState(Actor *actor);
extern void ShowDamageNumber_candidate(s32 targetIndex, s32 damage);
extern s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex);
extern s32 ResolveEnemyAttack(s32 attackerIndex, s32 defenderIndex);
extern void ApplyDamageToEnemyFighter(s32 damage, s32 fighterIndex);  // 0x08017F98
extern void ApplyDamageToAllyFighter(s32 damage, s32 fighterIndex);
extern void ShowFloatingDamageNumber(s32 damage, s32 color, s32 fighterIndex, s32 showZero);
extern void TickFloatingDamageNumber(Actor *actor);
extern void CheckBattleDefeat(void);
extern void PruneFaintedAndRebuildTurnOrder_candidate(s32 arg0);
extern void CheckBattleVictory(Actor *actor);                  // 0x080186E0
extern void ResetAllPartyLevelsTo1(void);
extern void ResetPartyHpMpAndStats(void);
void DeserializePartyStats(void);
void SerializePartyStats(void);
extern u32 GetMonsterDamageMax(u32 monster);
extern s32 GetPartyMemberXpToNextLevel(u32 slot);  // XP still needed for the next level
extern u32 GetPartyMemberLevelProgressPercent(u32 slot);
extern u32 GetPartyMemberLastLevelUpXp(u32 character);
// The Folio Bruti's spell rows, in display order (not SpellId order).
typedef enum {
    FolioSpellFlipendo          = 0,
    FolioSpellVerdimillious     = 1,
    FolioSpellIncendio          = 2,
    FolioSpellPetrificusTotalus = 3,
    FolioSpellWingardiumLeviosa = 4,
    FolioSpellSpongify          = 5,
    FolioSpellDiffindo          = 6,
    FolioSpellGlacius           = 7,
} FolioSpellRow;

// The spell's effectiveness (0-100) against a monster, by FolioSpellRow.
extern s32 GetMonsterSpellEffectiveness(s32 monsterIndex, s32 spell);
extern s32 GetMonsterRewardXp(u32 monster);
extern s32 ComputeEquippedDefensePercent(u32 character);
extern s32 ComputeEquippedAgility(u32 character);
extern s32 ComputeEquippedMagicDefensePercent(u32 character);
extern u32 GetMonsterLevel(u32 monster);
extern s32 GetMonsterRewardGold(u32 monster);
extern void PostActionBattleCheck(void);
extern void PlayFighterHurtSound(u16 damage, u8 fighterType);

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
