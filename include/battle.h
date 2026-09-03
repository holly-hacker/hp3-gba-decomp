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
