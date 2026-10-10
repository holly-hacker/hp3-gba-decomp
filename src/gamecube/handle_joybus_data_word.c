#include "types.h"
#include "gamecube.h"

// Appends the halfword in bits 8-23 of a JOYBUS_WORD_DATA word to the receive buffer after
// checking it against the checksum in bits 24-31. Returns 0 on an error.
u32 HandleJoybusDataWord(u32 word)
{
    u16 data;

    if (g_JoybusLinkState.wRecvRemaining != 0)
    {
        data = word >> 8;
        if (ComputeJoybusChecksum(data) == word >> 24)
        {
            g_JoybusLinkState.pRecvBuffer[g_JoybusLinkState.wRecvIndex] = data;
            g_JoybusLinkState.wRecvRemaining--;
            g_JoybusLinkState.wRecvIndex++;
            return 1;
        }
        g_JoybusLinkState.bError = JOYBUS_ERROR_RECV_CRC;
    }
    else
    {
        g_JoybusLinkState.bError = JOYBUS_ERROR_RECV_OVERRUN;
    }
    return 0;
}
