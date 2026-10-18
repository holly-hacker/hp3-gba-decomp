#include "types.h"
#include "pscreen_gamecube.h"

// Command 0x80: sends "ABC...Z".
void StageGameCubeTestPattern(u16 *pLength, u16 *pBuffer)
{
    u8 *pBytes = (u8 *)pBuffer;
    s32 i;

    for (i = 0; i < 26; i++)
        pBytes[i] = 'A' + i;

    *pLength = 26;
}
