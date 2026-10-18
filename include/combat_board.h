#pragma once

#include "types.h"

extern void DrawFighterStatsUi_candidate(s32 fighterType, s32 panelSlot);
extern void DrawEnemyStatsUi_candidate(s32 fighterIndex, s32 panelSlot);
extern void JitterEnemyTurnOrder(void);
extern void BuildTurnOrder(void);
extern void ReviveFighter_candidate(u8 pendingIdx);
extern void ClearParalyzedFighter_candidate(u8 fighterIndex);
extern void ClearPoisonedFighter_candidate(u8 fighterIndex);  // clears Poisoned, zeroes bPoisonDamage; CurePoison's shared helper
