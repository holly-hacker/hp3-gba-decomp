#include "types.h"
#include "game/game_timer.h"

void ResetAllGameTimers(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(g_aGameTimers); i++)
        ResetGameTimer(i);
}
