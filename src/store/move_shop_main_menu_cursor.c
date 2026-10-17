#include "types.h"
#include "store.h"
#include "store_inline.h"

void MoveShopMainMenuCursor(s32 row)
{
    if (g_FredAndGeorgesShop.bCursor != row)
    {
        DrawShopMainMenuRow(g_FredAndGeorgesShop.bCursor, 0);
        g_FredAndGeorgesShop.bCursor = row;
        DrawShopMainMenuRow(g_FredAndGeorgesShop.bCursor, 6);
    }
}
