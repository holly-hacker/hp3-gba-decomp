#include "types.h"
#include "serial/serial.h"

s32 GetSerialPlayerId(void)
{
    return g_SerialPlayerState.bPlayerId;
}
