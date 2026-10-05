#include "types.h"
#include "game/game_timer.h"

void ResetGameTimer(u32 index)
{
    g_aGameTimers[index].dwIndex = index;
    g_aGameTimers[index].dwMode = GameTimerStopped;
    g_aGameTimers[index].fPaused = 0;
    g_aGameTimers[index].dwValue = 0;
}
