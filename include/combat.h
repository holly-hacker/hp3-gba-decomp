#pragma once

#include "types.h"
#include "actor.h"
#include "battle/battle.h"

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
extern u32 g_bSelectedFighterSlot_candidate;
// One slot per active BattleFighter -- see docs/formats/battle-ui.md.
extern Actor *g_apFighterActors_candidate[7];
// Battle-message icon actor (shown alongside ShowBattleMessage's text),
// distinct from the 7 per-fighter Actors in g_apFighterActors_candidate.
extern Actor *g_pBattleMessageIconActor_candidate;
extern BattleMessageIconState g_BattleMessageIconState_candidate;
extern s32 g_anFaintedRosterIndices[4];
