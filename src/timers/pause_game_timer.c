#include "types.h"
#include "timers.h"

void PauseGameTimer(u32 index)
{
    g_aGameTimers[index].fPaused = 1;
}
