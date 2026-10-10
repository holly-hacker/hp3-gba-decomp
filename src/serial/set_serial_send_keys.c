#include "types.h"
#include "serial/serial.h"

// Selects whether ExchangeSerialFrame_candidate sends the held keys or idle messages.
void SetSerialSendKeys(u32 enable)
{
    if (enable)
        g_dwSerialPollFlags_candidate &= ~1;
    else
        g_dwSerialPollFlags_candidate |= 1;
}
