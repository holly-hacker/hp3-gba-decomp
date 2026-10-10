#include "types.h"
#include "font.h"

// Fills tileCount tiles of the column buffer with pixel value color.
void FillTextTileColumn(u32 *pBuf, u32 tileCount, u32 color)
{
    u32 words;

    if (gTextRenderState.is8bpp == 1)
    {
        color += (color << 24) + (color << 16) + (color << 8);
        words = tileCount * 16;
    }
    else
    {
        color &= 0xF;
        color += color << 4;
        color += color << 8;
        color += color << 16;
        words = tileCount * 8;
    }
    while (words--)
        *pBuf++ = color;
}
