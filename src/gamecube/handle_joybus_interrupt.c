#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Serial interrupt handler while a GameCube link session runs: dispatches the JOYCNT receive,
// send and reset flags, then acknowledges them. A rejected word drops the connection.
void HandleJoybusInterrupt(void)
{
    u16 flags;

    flags = REG_JOYCNT;

    if (((flags & JOYCNT_RECV) && !HandleJoybusCommandWord(REG_JOY_RECV))
        || ((flags & JOYCNT_SEND) && !HandleJoybusTransmit()))
    {
        REG_JOYSTAT = 0;
        g_JoybusLinkState.bState = JOYBUS_STATE_ERROR;
        g_JoybusLinkState.bConnected = 0;
        g_JoybusLinkState.bHandshake = JOYBUS_HANDSHAKE_NONE;
        g_JoybusLinkState.dwPeerGameCode = 0;
    }

    if (flags & JOYCNT_RESET)
        HandleJoybusReset();

    REG_JOYCNT = flags;
    g_JoybusLinkState.bTimeoutCounter = 0;
}
