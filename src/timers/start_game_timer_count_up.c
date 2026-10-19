#include "types.h"
#include "timers.h"

void StartGameTimerCountUp(u32 index)
{
    g_aGameTimers[index].dwIndex = index;
    g_aGameTimers[index].dwMode = GameTimerCountUp;
    g_aGameTimers[index].fPaused = 0;
    g_aGameTimers[index].dwValue = 0;
}
