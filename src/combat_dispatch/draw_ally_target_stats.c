#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dispatch.h"

void DrawAllyTargetStats(u32 slot)
{
    DrawFighterStatsUi(
        g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[slot]].bFighterType, 0);
}
