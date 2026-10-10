#include "types.h"
#include "font.h"

// Mirrors an 8x8 tile left to right in place, in the target's pixel format.
void FlipTileHorizontally(u8 *pTile)
{
    s32 row;
    s32 i;
    u8 *pRight;
    u8 left;
    u8 right;

    if (gTextRenderState.is8bpp == 1)
    {
        for (row = 8; row > 0; row--)
        {
            pRight = pTile + 7;
            for (i = 4; i > 0; i--)
            {
                left = *pTile;
                *pTile = *pRight;
                *pRight = left;
                pTile++;
                pRight--;
            }
            pTile += 4;
        }
    }
    else
    {
        for (row = 8; row > 0; row--)
        {
            pRight = pTile + 3;
            for (i = 2; i > 0; i--)
            {
                left = (*pTile >> 4) | (*pTile << 4);
                right = (*pRight >> 4) | (*pRight << 4);
                *pTile = right;
                *pRight = left;
                pTile++;
                pRight--;
            }
            pTile += 2;
        }
    }
}
