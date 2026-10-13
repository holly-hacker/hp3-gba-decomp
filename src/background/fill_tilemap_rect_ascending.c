#include "types.h"
#include "background.h"

void FillTilemapRectAscending(u16 *pTilemap, u32 x, u32 y, s32 w, s32 h, u16 tile)
{
    s32 row;
    s32 col;
    u16 *pCell;

    for (row = 0; row < h; row++)
    {
        pCell = pTilemap + (y + row) * 32 + x;
        for (col = 0; col < w; col++)
        {
            *pCell++ = tile;
            tile++;
        }
    }
}
