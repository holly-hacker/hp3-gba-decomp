#include "types.h"
#include "timers.h"

void StartGameTimerCountDown(u32 index, u32 ticks)
{
    g_aGameTimers[index].dwIndex = index;
    g_aGameTimers[index].dwMode = GameTimerCountDown;
    g_aGameTimers[index].fPaused = 0;
    g_aGameTimers[index].dwValue = ticks;
}
