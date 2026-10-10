#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "serial/serial.h"

// Puts the link port in multiplayer mode with both link interrupts off and resets every piece of
// session state.
void InitSerial(void)
{
    u32 i;
    u32 j;
    u32 zero;

    REG_IE &= ~0x40;
    REG_IE &= ~0x80;
    REG_SIOCNT = 0x2000;
    REG_SIOCNT &= ~0x40;
    REG_SIOCNT |= 0x4003;
    REG_SIOMLT_SEND = 0xFF;
    REG_RCNT = 7;
    REG_TM3CNT_H = 0;
    REG_TM3CNT_L = 0;

    g_SerialPlayerState.pSendCurrent = g_SerialPlayerState.awSendBuffers[0];
    g_SerialPlayerState.pSendNext = g_SerialPlayerState.awSendBuffers[0];
    // BUG: The arrays hold 2 players, not SERIAL_MAX_PLAYERS. Slots 2-3 zero
    // g_bSerialUnk03005A10, g_bSerialSeedReceived and g_dwSerialExchangeCount through
    // g_dwSerialUnk03005AA4, and leave two pointers in awRecvA[0].
    for (i = 0; i < SERIAL_MAX_PLAYERS; i++)
    {
        for (j = 0; j < 6; j++)
        {
            g_SerialPlayerState.awRecvA[i][j] = 0;
            g_SerialPlayerState.awRecvB[i][j] = 0;
        }
        g_SerialPlayerState.apRecvA[i] = g_SerialPlayerState.awRecvA[i];
        g_SerialPlayerState.apRecvB[i] = g_SerialPlayerState.awRecvB[i];
        g_awSerialKeysReceived[i] = 0;
    }

    g_SerialPlayerState.bPlayerCount = 0;
    g_SerialPlayerState.pfnWaitCallback = NULL;
    g_SerialPlayerState.bPlayerId = -1;
    g_SerialPlayerState.dwUnk_0x00 = -1;
    g_dwSerialUnk03005AA8 = 0;
    g_dwSerialConnectRetries = 0;
    g_dwSerialUnk03005AAC = 0;
    g_dwSerialUnk03005AA4 = 0;
    g_dwSerialUnk03005AB0 = 0;
    g_dwSerialExchangeCount = 0;
    g_dwSerialChecksumExchangeCount = 0;
    g_dwSerialMaxPlayers = 0;
    g_bSerialPlayerMask = 0;
    g_SerialLink.dwFlags = SERIAL_FLAG_FRAME_READY;
    REG_SIOMLT_SEND = 0xFFFF;

    for (i = 0; i < 2; i++)
    {
        zero = 0;
        bios_CPUSet(&zero, &g_aSerialRecvMessages[i], 0x05000000 | (sizeof(SerialMessage) / 4));
    }
    zero = 0;
    bios_CPUSet(&zero, &g_SerialSendMessage, 0x05000000 | (sizeof(SerialMessage) / 4));

    SetSerialWaitCallback(CountSerialConnectRetries);
    g_dwSerialUnk03005ABC = 0;
    REG_RCNT = 0;
    REG_SIOCNT = 0x2000;
    REG_SIOCNT |= 0x4003;
    ClearSerialChecksumRollBytes();
    g_SerialPlayerState.dwUnk_0x00 = -1;
    g_dwSerialPlayerCount = -1;
    g_dwSerialPollFlags_candidate &= ~1;
}
