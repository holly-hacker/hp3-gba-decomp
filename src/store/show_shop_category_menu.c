#include "types.h"
#include "menu/main_menu.h"
#include "shop.h"

void ShowShopCategoryMenu(void)
{
    s32 i;

    ClearShopSicklesBox();
    g_FredAndGeorgesShop.bCursor = g_FredAndGeorgesShop.bCategory;

    for (i = 0; i < 7; i++)
    {
        g_FredAndGeorgesShop.apRowObjects[i] = SpawnObject(i, 0x24, 0x20 + i * 16, g_aShopCategoryIcons[i].pPalette);
        SetObjectAnimData(g_FredAndGeorgesShop.apRowObjects[i], &g_aShopCategoryIcons[i], g_abShopMenuIconAnim, 0);
        DrawShopCategoryRow(i, i == g_FredAndGeorgesShop.bCursor ? 6 : 0);
    }

    g_FredAndGeorgesShop.pCursor = SpawnMenuCursorObject(4);
    g_FredAndGeorgesShop.pCursor->oam.hFlip = 1;
    g_FredAndGeorgesShop.pCursor->pfnTick = TickShopMenuCursor;
    SetMenuCursorPosition(g_FredAndGeorgesShop.pCursor, 0x1E, g_FredAndGeorgesShop.bCursor * 16 + 0x28);
}
