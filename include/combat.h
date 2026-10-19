#pragma once

#include "actor.h"

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
    /*0x04*/ Actor *pActor;
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
    /*0x2A*/ u8 bAgility;
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

// BattleFighter.bPendingActionKind: what the battle menu queued for DispatchPendingAction.
typedef enum {
    PendingActionNone        = 0,
    PendingActionUseItem     = 1,
    PendingActionSpecialMove = 2,
    PendingActionFlee        = 3,
    PendingActionInformus    = 4,
} PendingActionKind;

// Battle-round state, 0x14C8 bytes. Fields below are the ones touched by
// ResolvePlayerAttack/ResolveEnemyAttack and TickPlayerActionState_candidate.
typedef struct FightState {
    /*0x00*/ BattleFighter *pStagingFighters;
    /*0x04*/ BattleFighter *pFighters;
    /*0x08*/ BattleFighter *pPendingFighters_candidate;  // front-popped reinforcement queue, count at +0x1491
    /*0x0C*/ u8 pad_0C[0x818 - 0x0C];
    // One turn-order-icon container Actor* per active fighter slot,
    // allocated by SpawnTurnOrderIcon; each container's pLinkedActor_candidate
    // is its portrait sprite, which SetActorAnimFrame/SetFighterTurnOrderIconDone
    // actually animate.
    /*0x818*/ Actor *apTurnOrderIconActors[7];
    // ExitBattle's Folio Universitas/Help resume path snapshots every live
    // (0-bFighterCount) then pending (0-bPendingFighterCount_candidate)
    // fighter's Actor here, densely packed, before the real Actors are
    // torn down -- exactly 7 slots (the same total as g_apFighterActors_candidate)
    // fill this to FightState's 0x104C boundary.
    /*0x834*/ Actor aSuspendedFighterActors_candidate[7];
    /*0x104C*/ FixedPoint savedPos;  // copy of the attacker's Actor.pos
    /*0x1054*/ void *pAttackAnimActor_candidate;
    /*0x1058*/ u8 bAttackAnimState_candidate;
    /*0x1059*/ u8 aEnemySlotTurnOrderIndex[4];
    /*0x105D*/ u8 aAllySlotTurnOrderIndex[3];
    /*0x1060*/ u8 bScreenShakeTimer_candidate;
    /*0x1061*/ u8 bBattleState;              // TickBattleTurnStateMachine's dispatch value, 0-7
    /*0x1062*/ u8 bSavedBattleState;         // bBattleState stashed across state 5 (message wait), restored after
    /*0x1063*/ u8 pad_1063;
    /*0x1064*/ u32 dwStateJustEntered;       // one-shot flag consumed by each state's own tick, set whenever bBattleState changes
    /*0x1068*/ u16 wBattleStateTimer;        // generic per-state countdown, meaning is state-specific
    /*0x106A*/ u16 wNextFighterTurnKey_candidate;  // nFaintedFlag of the fighter after the active one (the first fighter on wrap), set by PruneFaintedAndRebuildTurnOrder_candidate
    /*0x106C*/ u8 bActiveFighterIndex;
    /*0x106D*/ u8 bMenuFighterIndex;
    /*0x106E*/ u8 bUnk106E;    // zeroed by InitializeBattle, only on a fresh (non-resumed) battle
    /*0x106F*/ u8 bFighterCount;
    /*0x1070*/ u8 bMenuScreen;  // TickBattleMenuInput's own screen selector; 0, 0xa, and bit 0x80 all mean no active screen
    /*0x1071*/ u8 pad_1071[0x1078 - 0x1071];
    /*0x1078*/ u32 dwTextTileCursor;  // DrawTextLines tile cursor of battle messages
    /*0x107C*/ u16 awPalette[0x200];  // BG and OBJ palette, DMAed to palette RAM at the HUD scanline
    /*0x147C*/ u8 pad_147C[0x147E - 0x147C];
    /*0x147E*/ u8 bActionDelayCounter_candidate;
    /*0x147F*/ u8 bWallEndLine;  // scanline ending the BG1 wall band (BG1VOFS 264 - line above it); moves with the camera
    /*0x1480*/ u8 bBonusRewardFlags;  // BattleRewardFlags; snapshotted to g_dwBattleRewardFlagsSnapshot by ExitBattle
    /*0x1481*/ u8 bEnemyScalePercent_candidate;  // set by InitializeBattle from Harry's level: 0x40/0x30/0x20 for level 0/1/2+
    /*0x1482*/ u8 pad_1482[0x1488 - 0x1482];
    /*0x1488*/ u32 dwRonSpecialUsed;  // set once Ron has used his Special Move this battle; grays the menu entry while nonzero
    /*0x148C*/ u32 dwHermioneSpecialUsed;  // set once Hermione has used her Special Move this battle; grays the menu entry while nonzero
    /*0x1490*/ u8 pad_1490;
    /*0x1491*/ u8 bPendingFighterCount_candidate;
    /*0x1492*/ u8 pad_1492[0x1494 - 0x1492];
    /*0x1494*/ u32 dwDefeatCheckPending_candidate;  // set to 1 by any lethal-HP-threshold hit (ApplyDamageToEnemyFighter,
                                                     // ApplyDamageToAllyFighter, spell insta-kills); cleared by whichever
                                                     // code path reacts to it after its own CheckBattleDefeat call
    /*0x1498*/ u8 pad_1498[0x149C - 0x1498];
    /*0x149C*/ u32 dwBattleResultPending;
    /*0x14A0*/ u32 dwPlayerActionActive_candidate;
    /*0x14A4*/ u8 pad_14A4;
    /*0x14A5*/ u8 abBattleResumeArgs_candidate[3];  // PushGameMode_3 arguments that re-enter Battle from the Help and
                                                    // Folio Universitas screens; [2] is 0xFF when no card-combo restriction applies
    /*0x14A8*/ u8 bPendingStatusMessageVariant_candidate;
    /*0x14A9*/ u8 pad_14A9[0x14AC - 0x14A9];
    /*0x14AC*/ struct {
        u16 wDamage;
        u8 bEffectId;
        u8 bFlag;
    } aFaintMessages_candidate[6];
    /*0x14C4*/ u8 bFaintMessageCount_candidate;
    /*0x14C5*/ u8 bDefeatWarpTarget;  // overworld warp-target index set by CheckBattleDefeat; state 6's PushGameMode_2 arg3
    /*0x14C6*/ u8 bFolioComboFirstCard;  // first card of the combo picked on the Folio Universitas screen for this attack, 0xFF for none
} FightState;

// FightState->bBonusRewardFlags bits.
typedef enum {
    ExtraExpBonus  = 0x01,
    GrantExtraXp   = 0x02,
    ForceItemDrop  = 0x04,
} BattleRewardFlags;

// The Folio Universitas card slot lives at +8 (dwCurrentGameModeArg2) in
// g_PrevGameModeStackContext (see modes.h): PushGameMode_2(0x26, slot, 0) stages
// the chosen card in the pending context's arg2, TickGameModeStack shifts
// pending -> current -> previous on pop, and battle code reads it back out
// of g_PrevGameModeStackContext once the Folio Universitas screen has returned.
#define g_nFolioUniversitasSlot g_PrevGameModeStackContext.dwCurrentGameModeArg2

// The currently-acting fighter's record. Shared by the turn state machine
// and the action-state tick.
#define ACTIVE_FIGHTER (g_pFightState->pFighters[g_pFightState->bActiveFighterIndex])

// Game mode handlers of the battle screen; see docs/memory-map/battle.md.

extern void InitializeBattle(void);
extern void UpdateBattle(void);
extern void ExitBattle(void);

extern FightState *g_pFightState;
extern BattleFighter g_aPartyMasterStats[];  // 0x48 stride, by FighterType
// Chain and actor row queued by PlayCutscene for the transition back.
extern u8 g_bPendingRoomScriptChain;
extern u8 g_bPendingRoomScriptRow;
// Rewards earned this battle, paid out by the combat result screen. The XP total is
// one pool shared by the whole party; reward grants also stage their Sickles
// amount in the gold variable.
extern u16 g_nBattleXpReward;
extern u16 g_nBattleGoldReward;
extern u32 g_dwOverworldMonstersDisabled;
extern u32 g_dwBattleRewardFlagsSnapshot;
