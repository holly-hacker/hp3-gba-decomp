#include "types.h"
#include "serial/serial.h"

void SetSerialCallbacks(void (*pfnReceive)(u32 word, u32 playerId), u32 (*pfnGetSendWord)(void))
{
    g_SerialLink.pfnReceive = pfnReceive;
    g_SerialLink.pfnGetSendWord = pfnGetSendWord;
}
