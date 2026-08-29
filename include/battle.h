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

// Battle-round state, 0x14C8 bytes. Only the fields ResolvePlayerAttack
// touches are laid out here; see docs/memory-map/battle.md for the rest.
typedef struct FightState {
    /*0x00*/ void *pStagingFighters;
    /*0x04*/ BattleFighter *pFighters;
} FightState;

extern FightState *g_pFightState;
extern u8 g_bSpellMissStreak;
