#include "types.h"
#include "timers.h"

void ResetAllGameTimers(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(g_aGameTimers); i++)
        ResetGameTimer(i);
}
