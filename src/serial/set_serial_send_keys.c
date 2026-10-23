#include "types.h"
#include "serial.h"

// Selects whether ExchangeSerialFrame sends the held keys or idle messages.
void SetSerialSendKeys(u32 enable)
{
    if (enable)
        g_dwSerialSendFlags &= ~1;
    else
        g_dwSerialSendFlags |= 1;
}
