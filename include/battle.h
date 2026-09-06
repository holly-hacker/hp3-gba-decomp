#pragma once

#include "types.h"

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

typedef struct Object Object;

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
    /*0x2A*/ u8 bStat_speed;
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
    /*0x40*/ s16 nSelectedTargetIndex;
    /*0x42*/ u8 bStatusFlags;
    /*0x43*/ u8 bPoisonDamage;
    /*0x44*/ u8 bParalysisEscapeChance;
} BattleFighter;

// Battle-round state, 0x14C8 bytes. Fields below are the ones touched by
// ResolvePlayerAttack/ResolveEnemyAttack and TickPlayerActionState_candidate;
// see docs/memory-map/battle.md for the rest.
typedef struct FightState {
    /*0x00*/ void *pStagingFighters;
    /*0x04*/ BattleFighter *pFighters;
    /*0x08*/ BattleFighter *pPendingFighters_candidate;  // front-popped reinforcement queue, count at +0x1491
    /*0x0C*/ u8 pad_0C[0x104C - 0x0C];
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
    /*0x1480*/ u8 pad_1480;
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

// A fighter's sprite/animation object. Only the fields touched by
// UpdateBattle/TickPlayerActionState are named; see those files' plate
// comments for the rest.
struct Object {
    u8 pad_00[0x08];
    u16 wFighterType;       // 0x08
    u8 pad_0A[0x02];        // -> 0x0C
    u32 dwFlags;            // 0x0C, bit 0x40000 = action-animation-done, bit 0x8000 = special-move trigger
    u8 pad_10[0x04];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 bUnk16;              // 0x16
    u8 pad_17[0x11];        // -> 0x28
    u32 dwUnk_0x28;         // 0x28, set to 1 by InitPlayerBattleActor_candidate
    u32 nX;                 // 0x2C, 16.16
    u32 nY;                 // 0x30, 16.16
    u8 pad_34[0x08];        // -> 0x3C
    u32 nVelX;              // 0x3C
    u32 nVelY;              // 0x40
    u8 pad_44[0x1C];        // -> 0x60
    u8 bAttackOutcomeState; // 0x60
    u8 pad_61[0x01];        // -> 0x62
    u16 wStagedDamage;      // 0x62
    u8 pad_64[0x18];        // -> 0x7C
    u8 bUnk_0x7C;           // 0x7C, zeroed by InitPlayerBattleActor_candidate
    u8 pad_7D[0x03];        // -> 0x80
    u32 dwStateTimer;       // 0x80
    u8 pad_84[0x02];        // -> 0x86
    u16 wUnk86;             // 0x86, zeroed alongside wMoveDuration
    u8 pad_88[0x02];        // -> 0x8a
    u16 wActionVariant;     // 0x8A
    u8 pad_8C[0x01];        // -> 0x8D
    u8 bActionState;        // 0x8D, the dispatch key
    u8 pad_8E[0x02];        // -> 0x90
    u8 bActionFlags;        // 0x90
    u8 bFighterIndex;       // 0x91
    u8 pad_92[0x06];        // -> 0x98
    void (*pfnTick)(struct Object *obj);  // 0x98, per-frame tick (player fighters: TickPlayerActionState)
    u8 pad_9C[0x08];        // -> 0xA4
    void *pLinkedObject_candidate;  // 0xA4; see docs/formats/room_scripts.md and
    u8 pad_A8[0x29];        // -> 0xD1
    u8 bFlags_0xD1;         // 0xD1, bit 0x20 set / bits 0x0C cleared by InitializeBattle
    u8 pad_D2[0x03];        // -> 0xD5
    u8 bGfxSlotAndFlags;    // 0xD5, upper nibble = graphics-cache slot
    u8 pad_D6[0x03];        // -> 0xD9
    u8 bAnimFrameDelay;     // 0xD9
    u8 pad_DA[0x0A];        // -> 0xE4
    u8 *pAnimFrameCursor;   // 0xE4
    u8 *pAnimFrameBase;     // 0xE8
};

extern void sub_080039E8(Object *obj);
extern void sub_0802D640(u8 priority);
extern void sub_0802D3BC(void);

// One slot per active BattleFighter -- see docs/formats/battle-ui.md.
extern Object *g_apFighterObjects_candidate[7];

// The Folio Universitas card slot lives at +8 in the previous-mode
// GameModeContext (0x03003F3C; PushGameMode_2's own arg2 write, see
// docs/memory-map/game_modes.md): PushGameMode_2(0x26, slot, 0) stages the
// chosen card in the pending context's nParam1, TickGameModeStack shifts
// pending -> current -> previous on pop, and battle code reads it back out
// of g_PrevGameModeCtx once the Folio Universitas screen has returned.
typedef struct GameModeContext {
    u32 dwMode;    // 0x00; high bit 0x80 marks pending
    s32 nParam0;   // 0x04
    s32 nParam1;   // 0x08; push arg2 / mode result slot
    u8 pad_0C[0x24 - 0x0C];
} GameModeContext;
extern GameModeContext g_PrevGameModeCtx;  // 0x03003F3C
#define g_nFolioUniversitasSlot g_PrevGameModeCtx.nParam1

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
extern u8 RollFighterParalysisEscape(s32 fighterIndex);  // 0 = acts normally, 1 = still paralyzed, 3 = escape roll succeeded
extern void sub_0800E0CC(s32 fighterType, s32 arg1);
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
extern void SelectAiTarget(s32 fighterIndex, s32 arg1);  // return value unused
extern void SetFighterAttackAnimState_candidate(Object *obj, s32 state);

extern u16 g_wHeldKeysBitmask_candidate;  // 0x030034F0, see ram_symbols.us.inc

extern void SetObjectFlippedX(Object *obj, s32 flip);
extern void sub_08015484(Object *obj, s32 state);
extern void sub_0800D264(void *ptr, s16 val1, s16 val2);  // 25-entry palette-flash/fade queue; val1/val2 real width is 16-bit
extern void PlaySoundById(s32 id);
extern void sub_08018B14(u16 damage, s32 fighterIndex);
extern void TriggerBattleEffect(s32 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, s32 damage);
extern s32 sub_08026CDC(s32 spellLevel);
extern s32 sub_08026CF0(s32 spellLevel);
extern u16 sub_08015334(s32 x, s32 fighterIndex);
extern u16 sub_080152CC(s32 x, s32 fighterIndex);
extern void sub_0800EB2C(s32 fighterIndex);
extern void ClearParalyzedFighter_candidate(s32 fighterIndex);
extern void PostActionBattleCheck(void);
extern void PushBattleState(s32 state);
extern void DecrementFolioUniversitasCard(s32 slot);
extern u8 g_abHarryCardEffectId[16];            // 0x080514C8
extern u8 g_aCardTargetingMeta[][2];            // 0x080514DE, stride 2
extern u8 g_abHermioneLectureEffectId[3];       // 0x0805150D
extern u8 g_abSpecialMoveEffectId[7];           // 0x0805150A
extern u16 g_nLastDamage;                       // 0x0300274A
extern u8 g_bLastTargetIndex;                   // 0x0300274C
extern void sub_080129F4(void);
extern void sub_08012B40(void);
extern void sub_080019C0(void *obj, s32 x, s32 y);  // sets Object+0x3c/+0x40, i.e. nVelX/nVelY directly
extern void sub_08003A30(void *obj, s16 a, s16 b, s16 c);  // a is stored pre-shifted << 8 into a 16-bit field
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
extern BattleFighter g_aPartyMasterStats[];     // 0x030024EC, 0x48 stride, by FighterType
extern u8 g_bDefeatWarpParam;                   // 0x03002748

// per-wFighterType windup-flash resource pointer row, stride 0xA0
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
extern void sub_08001958(Object *obj, s32 v);
extern void sub_08003A44(Object *obj, s32 a, s32 b, s32 c);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void sub_0800EBAC(void);
extern void sub_0800F16C(void);
extern void SetupBattleRoster_candidate(void);
extern u8 *sub_08012AC0(void);
extern void sub_08007800(u8 *a, s32 b, s32 c);
extern void sub_0800F5F0(void);
extern void PlayMusicModule(u8 moduleId);

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
extern u8 g_abBattleMusicByOverworldSlot[]; // 0x0804E28B, indexed by dwCurrentGameModeArg1_candidate
// Read here as a full word, not the byte docs/memory-map/game_modes.md's
// plate comment describes elsewhere -- real source likely declares it int.
extern u32 g_bCurrentRoomId;                // 0x03003B50

extern u16 g_nXpAccum;   // 0x0300260E
extern u16 g_nGoldAccum; // 0x03002610
