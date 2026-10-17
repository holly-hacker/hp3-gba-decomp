#include "types.h"
#include "background.h"
#include "color.h"

u32 LoadEmbeddedPaletteFromRow(const u8 *pBlob, u32 row)
{
    const u8 *pColors = pBlob + 2;
    u32 size;

    if (pBlob[0] & 1)
    {
        size = 0x200;
        sub_0800D244(pColors + row * 32, row * 16, 0x100 - row * 16);
    }
    else if (pBlob[0] & 2)
    {
        size = 0x20;
        sub_0800D244(pColors + row * 16, ((pBlob[1] >> 4) + row) * 16, 16);
    }
    else
        size = 0;

    return size;
}
