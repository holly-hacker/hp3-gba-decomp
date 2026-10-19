#pragma once

#include "types.h"

// Line height of the battle stats panels' DrawTextLines rows; the Japanese
// font's rows are a pixel taller.
#ifdef VERSION_JP
#define BATTLE_STATS_LINE_HEIGHT 9
#else
#define BATTLE_STATS_LINE_HEIGHT 8
#endif

extern void DrawFighterStatsUi(u8 fighterType, u8 panelSlot);
extern void DrawEnemyStatsUi(u8 fighterIndex, u8 panelSlot);
extern void JitterEnemyTurnOrder(void);
extern void BuildTurnOrder(void);
extern void ReviveFighter(u8 pendingIdx);
extern void ClearParalyzedFighter_candidate(u8 fighterIndex);
extern void ClearPoisonedFighter_candidate(u8 fighterIndex);  // clears Poisoned, zeroes bPoisonDamage; CurePoison's shared helper
