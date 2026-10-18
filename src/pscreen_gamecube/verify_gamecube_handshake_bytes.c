#include "types.h"
#include "pscreen_gamecube.h"

// Command 0x40: compares the received bytes with "abc...y". The result is not used.
void VerifyGameCubeHandshakeBytes(u16 *pLength, u16 *pBuffer)
{
    u8 *pBytes = (u8 *)pBuffer;
    s32 i;

    for (i = 0; i <= 24; i++)
    {
        if (pBytes[i] != 'a' + i)
            break;
    }
}
