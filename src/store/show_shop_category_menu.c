#include "types.h"
#include "store.h"
#include "cursor.h"

void ShowShopCategoryMenu(void)
{
    s32 i;

    ClearShopSicklesBox();
    g_FredAndGeorgesShop.bCursor = g_FredAndGeorgesShop.bCategory;

    for (i = 0; i < 7; i++)
    {
        g_FredAndGeorgesShop.apRowActors[i] = SpawnActor(i, 0x24, 0x20 + i * 16, g_aShopCategoryIcons[i].pPalette);
        SetActorAnimData(g_FredAndGeorgesShop.apRowActors[i], &g_aShopCategoryIcons[i], g_abShopMenuIconAnim, 0);
        DrawShopCategoryRow(i, i == g_FredAndGeorgesShop.bCursor ? 6 : 0);
    }

    g_FredAndGeorgesShop.pCursor = SpawnMenuCursorActor(4);
    g_FredAndGeorgesShop.pCursor->oam.hFlip = 1;
    g_FredAndGeorgesShop.pCursor->pfnTick = TickShopMenuCursor;
    SetMenuCursorPosition(g_FredAndGeorgesShop.pCursor, 0x1E, g_FredAndGeorgesShop.bCursor * 16 + 0x28);
}
