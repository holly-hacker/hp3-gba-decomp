#include "types.h"
#include "char_block.h"

void ResumeBgTileAnimations(void)
{
    u8 i;

    for (i = 0; i < g_bBgTileAnimationCount; i++)
        g_aBgTileAnimations[i].bFlags |= 2;
}
