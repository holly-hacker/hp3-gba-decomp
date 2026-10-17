#include "types.h"
#include "serial.h"

u32 GetSerialPlayerCount(void)
{
    return g_SerialPlayerState.bPlayerCount;
}
