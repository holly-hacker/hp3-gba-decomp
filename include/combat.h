#pragma once

#include "types.h"
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
