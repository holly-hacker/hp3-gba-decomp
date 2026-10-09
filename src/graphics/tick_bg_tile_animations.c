#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"

// Steps each running BG tile animation's frame timer and decodes the frame's tiles into the
// animation's buffer; CommitBgTileAnimations uploads them at vblank.
void TickBgTileAnimations(void)
{
    u8 i;
    BgTileAnimEntry *entry;
    const BgTileAnimFrame *pFrame;

    for (i = 0; i < g_bBgTileAnimationCount; i++)
    {
        entry = &g_aBgTileAnimations[i];
        if (!(entry->bFlags & 1))
            continue;
        if (!(entry->bFlags & 2))
            continue;

        pFrame = (const BgTileAnimFrame *)(g_aBgTileAnimations[i].pAnimation + 1) + entry->bFrame;
        entry->bTimer++;
        if (entry->bTimer >= pFrame->dwDuration && pFrame->dwDuration != 0)
        {
            entry->bTimer = 0;
            entry->bFrame++;
            if (entry->bFrame >= g_aBgTileAnimations[i].pAnimation->bFrameCount)
                entry->bFrame = 0;
            {
                const TileDataHeader *pTiles = pFrame->pTiles;
                u32 size = pTiles->wSize;
                UnpackTileData(pTiles, pTiles->aData, size, g_apBgTileAnimationBuffers[i]);
            }
            entry->bFlags |= 4;
        }
        else if (pFrame->dwDuration == 0)
        {
            g_aBgTileAnimations[i].bTimer = 0;
            if (g_aBgTileAnimations[i].bFrame >= g_aBgTileAnimations[i].pAnimation->bFrameCount)
                g_aBgTileAnimations[i].bFrame = 0;
            {
                const TileDataHeader *pTiles = pFrame->pTiles;
                u32 size = pTiles->wSize;
                UnpackTileData(pTiles, pTiles->aData, size, g_apBgTileAnimationBuffers[i]);
            }
            g_aBgTileAnimations[i].bFlags |= 4;
        }
    }
}
