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

// Live, in-battle per-fighter record, 0x48 bytes.
typedef struct BattleFighter {
    /*0x00*/ u8 bFighterType;   // FighterType
    /*0x01*/ u8 bRosterIndex;
    /*0x02*/ u8 unk02;
    /*0x03*/ u8 bSlotParam;
    /*0x04*/ void *pObject;
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
    /*0x1061*/ u8 pad_1061[0x106C - 0x1061];
    /*0x106C*/ u8 bActiveFighterIndex;
    /*0x106D*/ u8 bMenuFighterIndex;
    /*0x106E*/ u8 pad_106E;
    /*0x106F*/ u8 bFighterCount;
    /*0x1070*/ u8 pad_1070[0x147E - 0x1070];
    /*0x147E*/ u8 bActionDelayCounter_candidate;
    /*0x147F*/ u8 bCameraZoomStep_candidate;
    /*0x1480*/ u8 pad_1480[0x1491 - 0x1480];
    /*0x1491*/ u8 bPendingFighterCount_candidate;
    /*0x1492*/ u8 pad_1492[0x149C - 0x1492];
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
    /*0x14C5*/ u8 pad_14C5;
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
typedef struct Object {
    u8 pad_00[0x08];
    u16 wFighterType;       // 0x08
    u8 pad_0A[0x02];        // -> 0x0C
    u32 dwFlags;            // 0x0C, bit 0x40000 = action-animation-done, bit 0x8000 = special-move trigger
    u8 pad_10[0x04];        // -> 0x14
    u16 wMoveDuration;      // 0x14
    u8 pad_16[0x16];        // -> 0x2C
    u32 nX;                 // 0x2C, 16.16
    u32 nY;                 // 0x30, 16.16
    u8 pad_34[0x08];        // -> 0x3C
    u32 nVelX;              // 0x3C
    u32 nVelY;              // 0x40
    u8 pad_44[0x1C];        // -> 0x60
    u8 bAttackOutcomeState; // 0x60
    u8 pad_61[0x01];        // -> 0x62
    u16 wStagedDamage;      // 0x62
    u8 pad_64[0x1C];        // -> 0x80
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
    u8 pad_92[0x43];        // -> 0xD5
    u8 bGfxSlotAndFlags;    // 0xD5, upper nibble = graphics-cache slot
} Object;

extern void sub_080039E8(Object *obj);
extern void sub_0802D640(u8 priority);

// The Folio Universitas card slot lives at +8 in the previous-mode
// GameModeContext (0x03003F3C; PushGameMode_2's own arg2 write, see
// docs/memory-map/game_modes.md): PushGameMode_0(0x26, slot, 0) stages the
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
