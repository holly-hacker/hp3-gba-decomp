#include "types.h"
#include "items_list.h"

// Returns a free aIconGfx entry, or -1.
s32 AllocItemListIconGfx(void)
{
    u32 i;

    for (i = 0; i < g_ItemList.dwMaxRows + 1; i++)
    {
        if (!g_ItemList.abIconGfxUsed[i])
        {
            g_ItemList.abIconGfxUsed[i] = 1;
            return i;
        }
    }

    return -1;
}
