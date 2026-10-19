#include "types.h"
#include "oam.h"

u32 AllocOamEntry(void)
{
    u8 i;

    for (i = 0; i < 128; i++)
    {
        if (g_pOamShadowBuffer->aHalves[0][i].affineMode == 2)
        {
            ShowOamEntry(i);
            return i;
        }
    }

    return 0xFF;
}
