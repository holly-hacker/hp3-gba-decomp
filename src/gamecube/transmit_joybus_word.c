#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Loads the next send-buffer halfword into JOY_TRANS as a JOYBUS_WORD_SEND_DATA word with its
// checksum. Returns 0 when nothing is left to send.
u32 TransmitJoybusWord(void)
{
    u16 data;

    if (g_JoybusLinkState.wSendRemaining != 0)
    {
        data = g_JoybusLinkState.pSendBuffer[g_JoybusLinkState.wSendIndex];
        g_JoybusLinkState.wSendRemaining--;
        g_JoybusLinkState.wSendIndex++;
        REG_JOY_TRANS = (ComputeJoybusChecksum(data) << 24) | (data << 8) | JOYBUS_WORD_SEND_DATA;
        return 1;
    }

    g_JoybusLinkState.bError = JOYBUS_ERROR_SEND_OVERRUN;
    return 0;
}
