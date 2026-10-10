#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Handles a word the GameCube wrote to JOY_RECV. Before the link is up the only accepted word is
// the GameCube's game code. Afterwards a command byte opens a receive (0x40 up to
// wRecvCommandMax) or send (0x80 up to wSendCommandMax) transfer, answered with its halfword
// count, and JOYBUS_WORD_DATA words fill a receive transfer. Returns 0 when the word was rejected.
u32 HandleJoybusCommandWord(u32 word)
{
    u32 command;
    u16 recvLength;
    u16 sendLength;
    u16 receivedLength;

    if (g_JoybusLinkState.bConnected == 0)
    {
        if (g_JoybusLinkState.bHandshake == JOYBUS_HANDSHAKE_CODE_SENT)
        {
            if (word == g_JoybusLinkState.dwExpectedPeerGameCode)
            {
                REG_JOYSTAT = 0x30;
                g_JoybusLinkState.dwPeerGameCode = word;
                g_JoybusLinkState.bState = JOYBUS_STATE_CONNECTED;
                g_JoybusLinkState.bConnected = 1;
                g_JoybusLinkState.bCommand = 0;
                g_JoybusLinkState.bTimedOut = 0;
            }
            g_JoybusLinkState.bHandshake = JOYBUS_HANDSHAKE_NONE;
        }
        else
        {
            g_JoybusLinkState.bError = JOYBUS_ERROR_GAME_CODE_RECV;
            return 0;
        }
    }
    else
    {
        command = word & 0xFF;
        if (g_JoybusLinkState.bCommand == 0)
        {
            if (command >= JOYBUS_RECV_COMMAND_MIN && command <= g_JoybusLinkState.wRecvCommandMax)
            {
                g_JoybusLinkState.wRecvIndex = 0;
                g_JoybusLinkState.wRecvRemaining = (word >> 8) & 0xFF;
                if (g_JoybusLinkState.wRecvRemaining == 0)
                {
                    recvLength = 0;
                    g_JoybusLinkState.pfnCommand(command, &recvLength, g_JoybusLinkState.pRecvBuffer);
                    g_JoybusLinkState.bState = JOYBUS_STATE_RECEIVED;
                }
                else
                {
                    g_JoybusLinkState.bState = JOYBUS_STATE_RECEIVING;
                    g_JoybusLinkState.bCommand = command;
                }
                REG_JOY_TRANS = (ComputeJoybusChecksum(g_JoybusLinkState.wRecvRemaining) << 24)
                              | (g_JoybusLinkState.wRecvRemaining << 8) | command;
            }
            else if (command >= JOYBUS_SEND_COMMAND_MIN
                     && command <= g_JoybusLinkState.wSendCommandMax)
            {
                g_JoybusLinkState.bState = JOYBUS_STATE_SENDING;
                g_JoybusLinkState.bCommand = command;
                g_JoybusLinkState.pfnCommand(command, &sendLength, g_JoybusLinkState.pSendBuffer);
                g_JoybusLinkState.wSendIndex = 0;
                g_JoybusLinkState.wSendRemaining = (sendLength + 1) / 2;
                REG_JOY_TRANS = (ComputeJoybusChecksum(g_JoybusLinkState.wSendRemaining) << 24)
                              | (g_JoybusLinkState.wSendRemaining << 8) | command;
            }
        }
        else if (g_JoybusLinkState.bCommand >= JOYBUS_RECV_COMMAND_MIN
                 && g_JoybusLinkState.bCommand <= g_JoybusLinkState.wRecvCommandMax)
        {
            if (command == JOYBUS_WORD_DATA)
            {
                if (HandleJoybusDataWord(word))
                {
                    if (g_JoybusLinkState.wRecvRemaining == 0)
                    {
                        receivedLength = g_JoybusLinkState.wRecvIndex * 2;
                        g_JoybusLinkState.pfnCommand(g_JoybusLinkState.bCommand, &receivedLength,
                                                     g_JoybusLinkState.pRecvBuffer);
                        REG_JOY_TRANS = (ComputeJoybusChecksum(0) << 24) | g_JoybusLinkState.bCommand;
                        g_JoybusLinkState.bState = JOYBUS_STATE_RECEIVED;
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
                g_JoybusLinkState.bError = JOYBUS_ERROR_RECV_MISSING_PACKET;
                return 0;
            }
        }
        else
        {
            g_JoybusLinkState.bError = JOYBUS_ERROR_INVALID_COMMAND;
            return 0;
        }
    }
    return 1;
}
