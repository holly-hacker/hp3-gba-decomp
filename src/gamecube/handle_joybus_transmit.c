#include "types.h"
#include "gamecube.h"

// Runs after the GameCube read JOY_TRANS. Before the link is up this completes the game code
// handshake; during a send transfer it loads the next data halfword. Returns 0 on an error.
u32 HandleJoybusTransmit(void)
{
    if (g_JoybusLinkState.bConnected == 0)
    {
        if (g_JoybusLinkState.bHandshake == JOYBUS_HANDSHAKE_RESET)
        {
            g_JoybusLinkState.bHandshake = JOYBUS_HANDSHAKE_CODE_SENT;
        }
        else
        {
            g_JoybusLinkState.bError = JOYBUS_ERROR_GAME_CODE_SEND;
            return 0;
        }
    }
    // During a receive transfer JOY_TRANS keeps the last answer; only send transfers load data.
    else if (g_JoybusLinkState.bCommand != 0
             && (g_JoybusLinkState.bCommand < JOYBUS_RECV_COMMAND_MIN
                 || g_JoybusLinkState.bCommand > g_JoybusLinkState.wRecvCommandMax))
    {
        if ((s8)g_JoybusLinkState.bCommand < 0
            && g_JoybusLinkState.bCommand <= g_JoybusLinkState.wSendCommandMax)
        {
            if (TransmitJoybusWord())
            {
                if (g_JoybusLinkState.wSendRemaining == 0)
                {
                    g_JoybusLinkState.bState = JOYBUS_STATE_SENT;
                    g_JoybusLinkState.bCommand = 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            g_JoybusLinkState.bError = JOYBUS_ERROR_INVALID_MODE;
            return 0;
        }
    }
    return 1;
}
