#include "types.h"
#include "serial/serial.h"

// Copies each player's received buffer out to pRecvOut, then checksums pMessage and stages it as
// the next message to send. Mixing the exchange count and the RNG's last roll byte into the
// checksum makes it fail when the two GBAs drift apart. No caller has been found.
void SubmitSerialMessage(SerialMessage *pMessage, SerialMessage *pRecvOut)
{
    s32 i;
    s32 j;
    u16 *pDst;
    s32 sum;
    u8 *pBytes;
    u16 *pTemp;

    i = g_SerialPlayerState.bPlayerCount;
    while (--i != -1)
    {
        pDst = (u16 *)&pRecvOut[i];
        for (j = 0; j < 6; j++)
            pDst[j] = g_SerialPlayerState.apRecvB[i][j];
    }

    sum = 0;
    pMessage->wChecksum = 0;
    pBytes = (u8 *)pMessage;
    for (j = 0; j < (s32)sizeof(SerialMessage); j++)
        sum += pBytes[j];
    sum += g_dwSerialExchangeCount;
    sum += GetMt19937LastRollByte();
    LatchSerialChecksumRollByte();
    g_dwSerialChecksumExchangeCount = g_dwSerialExchangeCount;
    pMessage->wChecksum = -sum;

    for (j = 0; j < 6; j++)
        g_SerialPlayerState.pSendNext[j] = ((u16 *)pMessage)[j];

    if (g_SerialPlayerState.dwUnk_0x00 == -1)
    {
        pTemp = g_SerialPlayerState.pSendCurrent;
        g_SerialPlayerState.pSendCurrent = g_SerialPlayerState.pSendNext;
        g_SerialPlayerState.pSendNext = pTemp;
    }

    g_SerialLink.dwFlags &= ~SERIAL_FLAG_TRANSFER_KICKED;
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_FRAME_READY;
    g_SerialLink.dwFlags &= ~0x40000;
    g_SerialLink.dwFlags |= SERIAL_FLAG_TRANSFER_DONE;
    g_SerialLink.dwFlags |= SERIAL_FLAG_ROUND_COMPLETE;
}
