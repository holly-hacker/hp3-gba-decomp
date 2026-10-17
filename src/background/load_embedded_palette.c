#include "types.h"
#include "background.h"
#include "color.h"

u32 LoadEmbeddedPalette(const u8 *pBlob, u32 row, u32 rowCount)
{
    const u8 *pColors = pBlob + 2;
    u32 size;
    u32 firstColor;

    if (pBlob[0] & 1)
    {
        size = 0x200;
        firstColor = row << 4;
        if (rowCount > 16 - row)
            rowCount = 16 - row;
        sub_0800D244(pColors, firstColor, rowCount << 4);
    }
    else if (pBlob[0] & 2)
    {
        size = 0x20;
        sub_0800D244(pColors, ((pBlob[1] >> 4) + row) << 4, 16);
    }
    else
        size = 0;

    return size;
}
