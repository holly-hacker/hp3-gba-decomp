#pragma once

#include "types.h"
#include "mem.h"
#include "graphics.h"
#include "input.h"
#include "game_modes.h"

// See docs/memory-map/battle.md.

typedef enum {
    Harry    = 0,
    Hermione = 1,
    Ron      = 2,
    Buckbeak = 3,
    Enemy    = 0xFF,
} FighterType;

typedef enum {
    Flipendo          = 0,
    Informus          = 1,
    Verdimillious     = 2,
    Diffindo          = 3,
    Incendio          = 4,
    WingardiumLeviosa = 5,
    PetrificusTotalus = 6,
    Glacius           = 7,
    Fumos             = 8,
    Spongify          = 9,
} SpellId;

typedef enum {
    StatusNone       = 0,
    Hidden           = 0x01,
    Poisoned         = 0x02,
    PoisonImmune     = 0x04,
    AttackWeakened   = 0x08,
    Paralyzed        = 0x10,
    DefenseBoost     = 0x20,
    SpellPowerBoost  = 0x40,
} BattleStatusFlags;

// Live, in-battle per-fighter record, 0x48 bytes.
typedef struct BattleFighter {
    /*0x00*/ u8 bFighterType;   // FighterType
    /*0x01*/ u8 bRosterIndex;
    /*0x02*/ u8 unk02;
    /*0x03*/ u8 bSlotParam;
    /*0x04*/ Object *pObject;
    /*0x08*/ u16 wHp;
    /*0x0A*/ u16 wMp;
    /*0x0C*/ u16 wRewardXp;
    /*0x0E*/ u8 bLevel;
    /*0x0F*/ u8 bKnownSpellCount;
    /*0x10*/ u8 aSpellCastLevel[10];
    /*0x1A*/ u8 aSpellUsageProgress[10];
    /*0x24*/ u16 wHp_max;
    /*0x26*/ u16 wMp_max;
    /*0x28*/ u16 wRewardGold;
    /*0x2A*/ u8 bSpeed;
    /*0x2B*/ u8 bAccuracy;
    /*0x2C*/ u8 bCritChance;
    /*0x2D*/ u8 unk2D;
    /*0x2E*/ u8 bDefenseFactorPercent;
    /*0x2F*/ u8 bMagicDefensePercent;
    /*0x30*/ u16 wDamageRollMin;
    /*0x32*/ u16 wDamageRollMax;
    /*0x34*/ u8 bEffectivenessFlipendo;
    /*0x35*/ u8 bEffectivenessIncendio;
    /*0x36*/ u8 bEffectivenessVerdimillious;
    /*0x37*/ u8 bEffectivenessWingardiumLeviosa;
    /*0x38*/ u8 bEffectivenessGlacius;
    /*0x39*/ u8 bEffectivenessDiffindo;
    /*0x3A*/ u8 bSelectedActionIndex;
    /*0x3B*/ u8 bPendingActionKind;
    /*0x3C*/ u8 bSpellId;
    /*0x3D*/ u8 bSpellLevel;
    /*0x3E*/ u8 unk3E;
    // -1 when fainted (wHp == 0); 0 while alive; BuildTurnOrder also reuses
    // this as scratch space, temporarily overwriting it with a nonzero
    // "already placed in turn order" marker during its sort.
    /*0x40*/ s16 nFaintedFlag;
    /*0x42*/ u8 bStatusFlags;
    /*0x43*/ u8 bPoisonDamage;
    /*0x44*/ u8 bParalysisEscapeChance;
} BattleFighter;

// One MonsterTable record, 0x18 bytes; see docs/formats/folio_bruti.md.
typedef struct MonsterTableRow {
    u16 wHp;                 // 0x00
    u8 bLevel;               // 0x02
    u8 bSpeed;               // 0x03
    u8 bAccuracy;            // 0x04
    u8 bCritChance;          // 0x05
    u16 wDamageMin;          // 0x06
    u16 wDamageMax;          // 0x08
    u8 abEffectiveness[6];   // 0x0A
    u16 wRewardXp;           // 0x10
    u16 wRewardGold;         // 0x12
    u8 bSpecialChance;       // 0x14, not copied to BattleFighter
    u8 bSpecialId;           // 0x15, not copied to BattleFighter
    u16 wPad_0x16;           // 0x16
} MonsterTableRow;
extern const MonsterTableRow MonsterTable[];  // 0x0804F410, src/data/monsters.c

// One per-level row of Harry/Ron/Hermione's level-up stat tables, 12 bytes
// (last 2 always zero, not a real field). LevelUpFighter_candidate indexes
// these 0-based -- displayed Level N is row N-1; row 0 is never read back
// (a fresh Level-1 character never "levels up" into it). bDefenseFactorPercent
// is dead: RecomputeBaseStatsFromLevel_candidate resets it to 100 right after
// LevelUpFighter_candidate applies it. See docs/memory-map/battle.md.
typedef struct CharacterLevelEntry {
    u16 wHp_max;
    u16 wMp_max;
    u16 wXpDeltaForLevel;
    u8 bSpeed;
    u8 bAccuracy;
    u8 bDefenseFactorPercent;
    u8 bMagicDefensePercent;
    u8 pad_0A[2];
} CharacterLevelEntry;
extern const CharacterLevelEntry g_pHarryLevelTable[];     // 0x0804FE50, src/data/harry_levels.c
extern const CharacterLevelEntry g_pRonLevelTable[];       // 0x08050300, src/data/ron_levels.c
extern const CharacterLevelEntry g_pHermioneLevelTable[];  // 0x080507B0, src/data/hermione_levels.c

// One graphics-pointer table row, 0x20 bytes; only +0x08 is used here.
typedef struct MonsterGfxRow {
    u8 pad_00[0x08];
    s32 nEffectSlot_candidate;  // 0x08, AttachObjectEffectSlot arg
    u8 pad_0C[0x14];            // -> 0x20
} MonsterGfxRow;
extern MonsterGfxRow g_pMonsterGraphicsTable[];  // 0x0804E6B4
extern u8 g_pMonsterAnimFrameTable[];            // 0x08051E70, stride 0x60
// Shadow-companion graphics row; only +0x08 is used here.
typedef struct ShadowGfxRow {
    u8 pad_00[0x08];
    void *pEffectData;  // 0x08, AttachEffectOwner arg (compared by address)
} ShadowGfxRow;
extern ShadowGfxRow g_MonsterShadowGfxRow;       // 0x0804EF54, single row
extern u8 g_MonsterShadowAnimData[];             // 0x08053850

// Battle-round state, 0x14C8 bytes. Fields below are the ones touched by
// ResolvePlayerAttack/ResolveEnemyAttack and TickPlayerActionState_candidate;
// see docs/memory-map/battle.md for the rest.
typedef struct FightState {
    /*0x00*/ BattleFighter *pStagingFighters;
    /*0x04*/ BattleFighter *pFighters;
    /*0x08*/ BattleFighter *pPendingFighters_candidate;  // front-popped reinforcement queue, count at +0x1491
    /*0x0C*/ u8 pad_0C[0x834 - 0x0C];
    // ExitBattle's Folio Universitas/Help resume path snapshots every live
    // (0-bFighterCount) then pending (0-bPendingFighterCount_candidate)
    // fighter's Object here, densely packed, before the real Objects are
    // torn down -- exactly 7 slots (the same total as g_apFighterObjects_candidate)
    // fill this to FightState's 0x104C boundary.
    /*0x834*/ Object aSuspendedFighterObjects_candidate[7];
    /*0x104C*/ u32 nSavedPosX;      // 16.16, from Object+0x2C
    /*0x1050*/ u32 nSavedPosY;      // 16.16, from Object+0x30
    /*0x1054*/ void *pAttackAnimObject_candidate;
    /*0x1058*/ u8 bAttackAnimState_candidate;
    /*0x1059*/ u8 aEnemySlotTurnOrderIndex[4];
    /*0x105D*/ u8 aAllySlotTurnOrderIndex[3];
    /*0x1060*/ u8 bScreenShakeTimer_candidate;
    /*0x1061*/ u8 bBattleState;              // TickBattleTurnStateMachine's dispatch value, 0-7
    /*0x1062*/ u8 bSavedBattleState;         // bBattleState stashed across state 5 (message wait), restored after
    /*0x1063*/ u8 pad_1063;
    /*0x1064*/ u32 dwStateJustEntered;       // one-shot flag consumed by each state's own tick, set whenever bBattleState changes
    /*0x1068*/ u16 wBattleStateTimer;        // generic per-state countdown, meaning is state-specific
    /*0x106A*/ u8 pad_106A[0x106C - 0x106A];
    /*0x106C*/ u8 bActiveFighterIndex;
    /*0x106D*/ u8 bMenuFighterIndex;
    /*0x106E*/ u8 bUnk106E;    // zeroed by InitializeBattle, only on a fresh (non-resumed) battle
    /*0x106F*/ u8 bFighterCount;
    /*0x1070*/ u8 bMenuScreen;  // TickBattleMenuInput's own screen selector; 0, 0xa, and bit 0x80 all mean no active screen
    /*0x1071*/ u8 pad_1071[0x147E - 0x1071];
    /*0x147E*/ u8 bActionDelayCounter_candidate;
    /*0x147F*/ u8 bCameraZoomStep_candidate;
    /*0x1480*/ u8 bBonusRewardFlags;  // BattleRewardFlags; snapshotted to g_dwBattleRewardFlagsSnapshot by ExitBattle
    /*0x1481*/ u8 bEnemyScalePercent_candidate;  // set by InitializeBattle from Harry's level: 0x40/0x30/0x20 for level 0/1/2+
    /*0x1482*/ u8 pad_1482[0x1491 - 0x1482];
    /*0x1491*/ u8 bPendingFighterCount_candidate;
    /*0x1492*/ u8 pad_1492[0x1494 - 0x1492];
    /*0x1494*/ u32 dwDefeatCheckPending_candidate;  // set to 1 by any lethal-HP-threshold hit (ApplyDamageToFighter,
                                                     // spell insta-kills, the poison-tick loop); cleared by whichever
                                                     // code path reacts to it after its own CheckBattleDefeat call
    /*0x1498*/ u8 pad_1498[0x149C - 0x1498];
    /*0x149C*/ u32 dwBattleResultPending;
    /*0x14A0*/ u32 dwPlayerActionActive_candidate;
    /*0x14A4*/ u8 pad_14A4[0x14A8 - 0x14A4];
    /*0x14A8*/ u8 bPendingStatusMessageVariant_candidate;
    /*0x14A9*/ u8 pad_14A9[0x14AC - 0x14A9];
    /*0x14AC*/ struct {
        u16 wDamage;
        u8 bEffectId;
        u8 bFlag;
    } aFaintMessages_candidate[6];
    /*0x14C4*/ u8 bFaintMessageCount_candidate;
    /*0x14C5*/ u8 bDefeatWarpTarget;  // overworld warp-target index set by CheckBattleDefeat; state 6's PushGameMode_2 arg3
    /*0x14C6*/ u8 bAttackVfxId_candidate;
} FightState;

extern FightState *g_pFightState;
extern u8 g_bSpellMissStreak;

// FightState->bBonusRewardFlags bits, see docs/memory-map/battle.md.
typedef enum {
    ExtraExpBonus  = 0x01,
    GrantExtraXp   = 0x02,
    ForceItemDrop  = 0x04,
} BattleRewardFlags;

extern u32 g_dwBattleRewardFlagsSnapshot;
extern s32 g_anFaintedRosterIndices[4];

extern void sub_080039E8(Object *obj);
extern void sub_0802D640(u8 priority);
extern void sub_0802D3BC(void);

// One slot per active BattleFighter -- see docs/formats/battle-ui.md.
extern Object *g_apFighterObjects_candidate[7];

// The Folio Universitas card slot lives at +8 (dwCurrentGameModeArg2) in
// g_PrevGameModeCtx (see game_modes.h): PushGameMode_2(0x26, slot, 0) stages
// the chosen card in the pending context's arg2, TickGameModeStack shifts
// pending -> current -> previous on pop, and battle code reads it back out
// of g_PrevGameModeCtx once the Folio Universitas screen has returned.
#define g_nFolioUniversitasSlot g_PrevGameModeCtx.dwCurrentGameModeArg2

extern u32 g_aBgScrollState[];  // 0x03001E80; [0x25] == 0x03001F14
extern u8 g_abBgPriority[];     // 0x03003F8C; [4] == 0x03003F90

// The currently-acting fighter's record. Shared by the turn state machine
// and the action-state tick.
#define ACTIVE_FIGHTER (g_pFightState->pFighters[g_pFightState->bActiveFighterIndex])

extern void TickBattleTurnStateMachine(void);
extern void sub_080130B4(s32 fighterIndex);
extern void sub_0800FEE0(s32 fighterIndex);
extern void sub_08013108(u8 fighterIndex);        // cursor/highlight-to-fighter
extern void ShowFloatingDamageNumber_candidate(s32 damage, s32 code, s32 fighterIndex, s32 flag);
extern void ApplyStatusDamageToFighter_candidate(s32 damage, s32 fighterIndex);
extern void sub_08018304(void);
extern void sub_08018460(s32 arg0);
extern u8 RollFighterParalysisEscape(u8 fighterIndex);  // 0 = acts normally, 1 = still paralyzed, 3 = escape roll succeeded
extern void DrawFighterStatsUi_candidate(s32 fighterType, s32 panelSlot);
// ShowBattleMessage's first parameter; what each case renders is in
// docs/memory-map/battle-ui.md's "ShowBattleMessage -- case -> dialog text
// table". SpecialAbilityText (3) shares the switch's trailing default body.
// Case 5 covers the whole attack-result dispatch, not just crits.
typedef enum {
    SpellLevelUp      = 0,
    EscapeBlocked     = 1,
    SpecialMoveAnnounce = 2,
    SpecialAbilityText = 3,
    ActionAnnounce    = 4,
    AttackResult      = 5,
    FaintResult       = 6,
    ItemUseAnnounce   = 7,
    StatusRestore     = 8,
    SpCost            = 9,
    MpCost            = 10,
    Victory           = 11,
    Defeat            = 12,
    CantMove          = 13,
    CanMoveAgain      = 14,
    // battle-ui.md calls this case AttackWeakened; renamed because
    // BattleStatusFlags already owns that name.
    AttackWeakenedMessage = 15,
    // battle-ui.md calls this case Hidden; renamed for the same reason.
    HiddenFromView    = 16,
    ImmuneToParalysis = 17,
} BattleMessageCode;
// bPendingStatusMessageVariant_candidate's "none" value, written at battle
// init: the guard at each ShowBattleMessage(AttackResult, 0, variant) site
// skips the second message while it holds.
#define NO_PENDING_STATUS_MESSAGE_VARIANT 0x12

extern void ShowBattleMessage(s32 code, s32 arg1, s32 arg2);
extern void OpenBattleTopMenu(s32 fighterIndex, s32 arg1);
extern void TickBattleMenuInput(void);
extern void DispatchPendingAction(s32 fighterIndex);
extern void DrawEnemyStatsUi_candidate(s32 fighterIndex, s32 panelSlot);
extern void SetFighterAttackAnimState_candidate(Object *obj, u8 state);
extern void UpdateFighterFlashEffect_candidate(Object *obj);  // 0x08015574
extern void CheckBattleVictory(Object *obj);                  // 0x080186E0
extern s32 ResolveEnemyAttack(s32 attackerIndex, s32 defenderIndex);
extern void RollMonsterSpecialEffect(s32 monsterIndex, s32 targetFighterIndex, s32 damage);
extern void ShowDamageNumber_candidate(s32 targetIndex, s32 damage);
extern void sub_080039F8(Object *obj);
extern void sub_08003A0C(Object *obj);
extern void sub_0801BCB0(void *linkedObject);
extern void FreeObject(Object *obj);
extern void ReleaseObjectAffineSlot(Object *obj);
extern void SetObjectAffineTransform(Object *obj, u32 nScaleX, u32 nScaleY, s32 wAngle, s32 bMode);
extern void StartObjectAffineScaleTween(Object *obj, u32 nTargetScaleX, u32 nTargetScaleY, s32 nFrames);  // ramps nAffineScaleX/Y to the target over nFrames ticks (0 = set immediately)

extern void SetObjectFlippedX(Object *obj, s32 flip);
extern void SetPlayerObjectAnim(Object *obj, s32 state);   // 0x08015484, party fighter anim tables
extern void SetMonsterObjectAnim(Object *obj, s32 state);  // 0x0801539C, monster gfx tables + shadow
extern void sub_0800D264(void *ptr, s16 val1, s16 val2);  // 25-entry palette-flash/fade queue; val1/val2 real width is 16-bit
extern void PlaySoundById(s32 id);
extern void sub_08018B14(u16 damage, s32 fighterIndex);
extern Object *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage);
extern s32 sub_08026CDC(s32 spellLevel);
extern s32 sub_08026CF0(s32 spellLevel);
extern u16 sub_08015334(s32 x, s32 fighterIndex);
extern u16 sub_080152CC(s32 x, s32 fighterIndex);
extern void ClearPoisonedFighter_candidate(u8 fighterIndex);  // clears Poisoned, zeroes bPoisonDamage; CurePoison's shared helper
extern void ClearParalyzedFighter_candidate(u8 fighterIndex);
extern void PostActionBattleCheck(void);
extern void PushBattleState(s32 state);
extern void DecrementFolioUniversitasCard(s32 slot);
extern u8 g_abHarryCardEffectId[16];            // 0x080514C8
extern u8 g_aCardTargetingMeta[][2];            // 0x080514DE, stride 2
extern u8 g_abHermioneLectureEffectId[3];       // 0x0805150D
extern u8 g_abSpecialMoveEffectId[7];           // 0x0805150A
extern u16 g_nLastDamage;                       // 0x0300274A
extern u8 g_bLastTargetIndex;                   // 0x0300274C
// Battle-effect staging area at 0x03002750. TriggerBattleEffect fills the
// fields below before spawning the effect object; the low bytes belong to
// other battle state (see docs/memory-map/battle.md).
typedef struct EffectStaging {
    u8 pad_00[0x1A];
    u16 wTimer_candidate;
    u16 wTimerMax_candidate;
    u16 wContextValue;
    u8 bScriptParam;
    u8 bSlotParam;
    u8 bTargetIndex;
    u8 bCasterIndex;
    u8 pad_24;
    u8 bStateA_candidate;
    u8 bStateB_candidate;
    u8 bIdStaged_candidate;
} EffectStaging;
extern EffectStaging g_effectStaging;                 // 0x03002750
extern Object *CreateEffectScriptObject(s32 effectId, s32 kind);  // 0x08018BE0
extern void sub_080129F4(void);
extern void sub_08012B40(void);
extern void sub_080019C0(void *obj, s32 x, s32 y);  // sets Object+0x3c/+0x40, i.e. nVelX/nVelY directly
extern void sub_08003A30(void *obj, s32 a, s16 b, s16 c);  // a is shifted << 8 inside and stored to a 16-bit field
extern void sub_0802D64C(s16 delta);
extern void sub_08012A38(void);
extern void ShowDamageNumber_candidate(s32 targetIndex, s32 damage);
extern void SnapObjectPosition(Object *obj, u32 x, u32 y);
extern void StartObjectMove(Object *obj, u32 x, u32 y, s16 mode);
extern void ShowItemUseResult(Object *obj, s32 targetIndex);
extern s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex);
extern void ApplyDamageToFighter(u16 damage, u8 fighterIndex);  // 0x08017F98
extern u8 g_abSpellEffectScriptId[][3];         // 0x080538B0, [spellId][level]
extern u16 g_awSpellMpCost[][3];                // 0x08053964, [spellId][level]
// 16.16 position pair. Object+0x2C and FightState+0x104C hold one each, and
// the battle code copies between them as a single 8-byte unit.
typedef struct Point1616 {
    u32 nX;
    u32 nY;
} Point1616;
// Screen anchor an attacker walks to, per target's BattleFighter.bSlotParam,
// as {x, y} in whole pixels; the monster's own {x, y} extent in
// g_aMonsterAttackOffset_candidate is subtracted off to get the destination.
extern u8 g_aBattleSlotAnchorPos_candidate[][2];  // 0x080539A0, [bSlotParam]
extern u8 g_aMonsterAttackOffset_candidate[][2];  // 0x0804FB9C, [rosterIndex]
extern BattleFighter g_aPartyMasterStats[];     // 0x030024EC, 0x48 stride, by FighterType
extern u8 g_bDefeatWarpParam;                   // 0x03002748

// per-wObjectType windup-flash resource pointer row, stride 0xA0
typedef struct AnimFlashRow {
    u8 pad_00[0x08];
    s32 nEffectSlotLive;        // 0x08, AttachObjectEffectSlot arg when the fighter is alive
    u8 pad_0C[0x5C];           // -> 0x68
    void *pWindupResourceB;    // 0x68
    u8 pad_6C[0x0C];           // -> 0x78
    void *pWindupResourceA;    // 0x78
    u8 pad_7C[0x04];           // -> 0x80
    void *pAssetRecordFainted; // 0x80, SetObjectAssetRecord arg when wHp == 0
    u8 pad_84[0x04];           // -> 0x88
    s32 nEffectSlotFainted;    // 0x88, AttachObjectEffectSlot arg when wHp == 0
    u8 pad_8C[0x14];           // -> 0xA0
} AnimFlashRow;
extern AnimFlashRow g_aFighterAnimTable[];  // 0x08051248, UNCONFIRMED row count
extern u8 g_aFighterAnimDataTable[];        // 0x08051560, stride 0x244, contents undecoded

extern void ClearResourceCacheSlots(void);
extern Object *AllocObjectOfType(s32 type);
extern Object *AllocDefaultObject(void);
extern u8 AttachObjectEffectSlot_candidate(Object *obj, s32 effectPtr);
extern void SetObjectAssetRecord(Object *obj, void *rec);
extern void SetObjectAnimData(Object *obj, void *a, void *b, s32 c);
extern void TickPlayerActionState(Object *obj);
extern void TickFighterAttackAnimState_candidate(Object *obj);  // 0x08015608
extern void AttachEffectOwner_candidate(Object *obj, void *pEffectData);  // 0x08030878
extern void sub_08001958(Object *obj, s32 v);
extern void sub_08003A44(Object *obj, s32 a, s32 b, s32 c);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void InitBattleBackground_candidate(void);
extern void RestoreFighterObjects_candidate(void);
extern void SetupBattleRoster(void);
extern u32 GetPartyPresenceMask(void);
extern u8 GetPartySize(void);
extern void JitterEnemyTurnOrder(void);
extern void BuildTurnOrder(void);
extern void SpawnTurnOrderIcon(u32 rosterIndexOrFighterType, u32 isAlly, u32 turnOrderIndex, u32 gfxSlot);
extern Object *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex);
extern Object *InitMonsterBattleActor(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex);
// Live save-adjacent state block at 0x03003180 (money, playtime, save flags,
// ...); only the doc-level array's +0x10 offset is pinned here, the rest
// stays padding until another reader needs it. See docs/formats/save.md.
// Member (not direct-symbol) access reproduces the ROM's base+0x10 address
// shape, shared by three code sites.
typedef struct {
    u8 pad_00[0x10];
    u8 abMonsterDocLevel[69];
} SaveStateBlock;
extern SaveStateBlock g_saveStateBlock;  // 0x03003180
extern u8 *GetBattleBackgroundData_candidate(void);
extern void LoadEmbeddedPalette_candidate(u8 *blob, s32 paletteRowOffset, s32 rowCount);
extern void ResumeBattleAfterSubmode_candidate(void);
extern void PlayMusicModule(u8 moduleId);

// ExitBattle's remaining callees -- generic engine/graphics teardown run on
// every battle exit, not battle logic; not otherwise analyzed.
extern void sub_08030960(s32 arg0);
extern void sub_080316D4(void);
extern void sub_0803171C(void);
extern void sub_0800D2DC(void);
extern void sub_08031668(s32 arg0, s32 arg1);
extern void sub_0803D3E8(s32 arg0, s32 arg1);
extern void sub_08026254(void);
extern void sub_0802D6B8(void);
extern void sub_08007A90(void);
extern void sub_0804542C(void);
extern void ClearFighterObjectFlag_candidate(u8 fighterIndex);  // 0x08012CB4
extern void sub_0802B0F4(void);  // Folio Universitas exit-arg3 teardown

// Battle-message icon object (shown alongside ShowBattleMessage's text),
// distinct from the 7 per-fighter Objects in g_apFighterObjects_candidate.
extern Object *g_pBattleMessageIconObject_candidate;  // 0x03002684
extern u32 g_bSelectedFighterSlot_candidate;          // 0x03002660

// bIndex/dwParam are adjacent globals (0x03002688/0x0300268C) accessed
// through one base address in the real code, hence one struct here.
typedef struct {
    u8 bIndex;    // sentinel 0xFF = none pending
    u8 pad[3];
    u32 dwParam;
} BattleMessageIconState;
extern BattleMessageIconState g_BattleMessageIconState_candidate;  // 0x03002688

extern u8 g_abBattleMusicByRoom[];          // 0x0804E254, indexed by g_bCurrentRoomId
extern u8 g_abBattleMusicByOverworldSlot[]; // 0x0804E28B, indexed by dwCurrentGameModeArg1
// Read here as a full word, not the byte docs/memory-map/game_modes.md's
// plate comment describes elsewhere -- real source likely declares it int.
extern u32 g_bCurrentRoomId;                // 0x03003B50

extern u16 g_nXpAccum;   // 0x0300260E
extern u16 g_nGoldAccum; // 0x03002610
