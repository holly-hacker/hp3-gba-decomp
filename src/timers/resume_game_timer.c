#include "types.h"
#include "timers.h"

void ResumeGameTimer(u32 index)
{
    g_aGameTimers[index].fPaused = 0;
}
