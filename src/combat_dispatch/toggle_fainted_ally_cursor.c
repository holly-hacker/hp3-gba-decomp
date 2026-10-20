#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"

// Moves the pending fighter cursor to the other of the two pending fighters.
void ToggleFaintedAllyCursor(void)
{
    if (g_pFightState->bFaintedAllyCount == 1)
        g_pFightState->bMenuCursor = 0;
    else
        g_pFightState->bMenuCursor ^= 1;
}
