#include "types.h"
#include "background.h"

void SetTilemapRectPalette(u16 *pTilemap, u32 x, u32 y, s32 w, s32 h, u16 palBank)
{
    s32 row;
    s32 col;
    u16 *pCell;
    u16 cell;

    for (row = 0; row < h; row++)
    {
        pCell = pTilemap + (y + row) * 32 + x;
        for (col = 0; col < w; col++)
        {
            cell = *pCell & 0xFFF;
            cell |= palBank << 12;
            *pCell++ = cell;
        }
    }
}
