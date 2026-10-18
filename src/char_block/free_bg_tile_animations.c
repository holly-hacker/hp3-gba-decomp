#include "types.h"
#include "char_block.h"
#include "mem.h"

void FreeBgTileAnimations(void)
{
    u32 i;

    StopAllBgTileAnimations();
    for (i = 0; i < g_bBgTileAnimationCount; i++)
    {
        FreeBlock(g_apBgTileAnimationBuffers[i]);
        g_apBgTileAnimationBuffers[i] = NULL;
    }
    g_bBgTileAnimationCount = 0;
}
