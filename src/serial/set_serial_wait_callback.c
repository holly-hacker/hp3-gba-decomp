#include "types.h"
#include "serial/serial.h"

void SetSerialWaitCallback(s32 (*pfnWaitCallback)(void))
{
    g_SerialPlayerState.pfnWaitCallback = pfnWaitCallback;
}
