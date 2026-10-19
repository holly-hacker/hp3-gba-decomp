#include "types.h"
#include "timers.h"

u32 GetGameTimerValue(u32 index)
{
    return g_aGameTimers[index].dwValue;
}
