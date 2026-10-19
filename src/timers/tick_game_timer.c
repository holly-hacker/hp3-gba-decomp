#include "types.h"
#include "timers.h"

u32 TickGameTimer(u32 index)
{
    u32 expired;

    switch (g_aGameTimers[index].dwMode)
    {
    case GameTimerStopped:
        expired = 1;
        break;
    case GameTimerCountDown:
        if (g_aGameTimers[index].dwValue == 0)
        {
            expired = 1;
        }
        else if (g_aGameTimers[index].fPaused)
        {
            expired = 0;
        }
        else
        {
            g_aGameTimers[index].dwValue--;
            expired = g_aGameTimers[index].dwValue == 0;
        }
        break;
    case GameTimerCountUp:
        if (!g_aGameTimers[index].fPaused)
            g_aGameTimers[index].dwValue++;
        expired = 0;
        break;
    default:
        expired = 0;
        break;
    }

    return expired;
}
