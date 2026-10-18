#include "types.h"
#include "char_block.h"
#include "mem.h"

// Adds an active, running animation with its first frame pending upload, and allocates the buffer
// its frames decode into. Flag 8 uploads that buffer with one DMA at vblank.
void RegisterBgTileAnimation(const void *pTable, const void *pBgControls, u32 flags)
{
    const BgTileAnimHeader *pAnimation = pTable;

    g_aBgTileAnimations[g_bBgTileAnimationCount].pAnimation = pAnimation;
    g_aBgTileAnimations[g_bBgTileAnimationCount].pBgControl = pBgControls;
    g_aBgTileAnimations[g_bBgTileAnimationCount].wTileOffset = pAnimation->wTileOffset;
    g_aBgTileAnimations[g_bBgTileAnimationCount].bFrame = 0;
    g_aBgTileAnimations[g_bBgTileAnimationCount].bTimer = 0;
    g_aBgTileAnimations[g_bBgTileAnimationCount].bFlags = flags;
    g_aBgTileAnimations[g_bBgTileAnimationCount].bFlags |= 7;
    g_apBgTileAnimationBuffers[g_bBgTileAnimationCount] = AllocZeroed(pAnimation->dwBufferSize);
    g_bBgTileAnimationCount++;
}
