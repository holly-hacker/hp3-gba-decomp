#include "types.h"
#include "buckbeak_minigame.h"

s32 FindFreeBuckbeakMinigameRing(void)
{
    s32 i;

    for (i = 0; i < BUCKBEAK_MINIGAME_RING_COUNT; i++)
    {
        if (g_pBuckbeakMinigame->aRings[i].bActive == 0)
            return i;
    }

    return -1;
}
