#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"

// Steps the target cursor by step until it is on an occupied enemy slot.
void MoveEnemyTargetCursor(s32 step)
{
    g_pFightState->bMenuCursor = WrapMenuCursor(g_pFightState->bMenuCursor, 2);
    while (g_pFightState->aEnemySlotTurnOrderIndex[g_pFightState->bMenuCursor] == 0xFF) {
        g_pFightState->bMenuCursor += step;
        g_pFightState->bMenuCursor = WrapMenuCursor(g_pFightState->bMenuCursor, 2);
    }
}
