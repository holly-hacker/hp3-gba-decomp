#include "palette.h"

void ClearObjPaletteSlots(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aObjPaletteSlots); i++)
    {
        g_aObjPaletteSlots[i].pData = NULL;
        g_aObjPaletteSlots[i].wRefcount = 0;
        g_aObjPaletteSlots[i].wFlags = 0;
    }
}
