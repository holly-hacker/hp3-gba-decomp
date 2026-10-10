#include "types.h"
#include "serial/serial.h"

// True if the message's checksum matches its bytes, the sender's exchange count and RNG byte as
// latched locally.
u32 VerifySerialMessageChecksum(SerialMessage *pMessage)
{
    u32 i;
    s32 sum;
    s32 checksum;
    u8 *pBytes;

    sum = 0;
    checksum = pMessage->wChecksum;
    pMessage->wChecksum = 0;
    pBytes = (u8 *)pMessage;
    for (i = 0; i < sizeof(SerialMessage); i++)
        sum += pBytes[i];
    sum += g_dwSerialChecksumExchangeCount;
    sum += GetSerialChecksumRollByte();
    pMessage->wChecksum = checksum;
    if ((u16)(sum + checksum) == 0)
        return 1;
    return 0;
}
