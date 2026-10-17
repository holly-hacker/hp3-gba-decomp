#include "types.h"
#include "serial.h"

s32 GetSerialPlayerId(void)
{
    return g_SerialPlayerState.bPlayerId;
}
