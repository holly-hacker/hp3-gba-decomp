#include "types.h"
#include "font.h"
#include "mem.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "text_actor.h"

// Draws one line of *ppText (advancing it) into a text actor's VRAM tiles.
// The renderer lays the text out as 8-pixel columns of two tiles; each
// 32-pixel strip copies the columns' top tiles to its first row and, for text
// taller than 8 pixels, their bottom tiles to its second.
void DrawTextActorText(Actor *pActor, const u8 **ppText)
{
    u16 *pTilemap;
    Tile4bpp *pTiles;
    Tile4bpp *pSrc;
    Tile4bpp *pDest;
    s32 charBudget;
    s32 strips;
    s32 strip;
    s32 column;

    charBudget = 0x7FFFFFFF;
    ResizeTextActor(pActor, *ppText);
    pTilemap = AllocBlock(0x78);
    pTiles = AllocZeroed((pActor->oam.bpp8 + 1) * 0x780);
    SaveTextTarget();
    SetTextTarget(pTilemap, (u8 *)pTiles, pActor->oam.bpp8);
    DrawTextLine(0, 0, 0, TEXT_ACTOR_MAX_WIDTH, ppText, 0, &charBudget);

    pSrc = pTiles;
    pDest = (Tile4bpp *)&OBJ_VRAM_TILES[pActor->wVramTileAllocId * 32];
    strips = pActor->anim.unk_DC.wOamStripCount;
    if (TEXT_ACTOR_HEIGHT(pActor) <= 8)
    {
        pActor->oam.size = 1;  // 32x8
        bios_CPUFastSet(pSrc, pDest, strips * 32);
    }
    else
    {
        pActor->oam.size = 2;  // 32x16
        for (strip = 0; strip < strips; strip++)
        {
            for (column = 4; column > 0; column--)
            {
                pDest[0] = *pSrc++;
                pDest[4] = *pSrc++;
                pDest++;
            }
            pDest += 4;
        }
    }

    RestoreTextTarget();
    FreeBlock(pTiles);
    FreeBlock(pTilemap);
}
