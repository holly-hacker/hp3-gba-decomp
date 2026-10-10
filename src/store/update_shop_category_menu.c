#include "types.h"
#include "graphics/audio.h"
#include "input.h"
#include "shop.h"

void UpdateShopCategoryMenu(void)
{
    if (g_wKeysPressed & KeyA)
    {
        g_FredAndGeorgesShop.pCursor->oam.objMode = 1;
        g_FredAndGeorgesShop.bCategory = g_FredAndGeorgesShop.bCursor;
        PlaySoundById(1);
        StartShopScreenTransition(ShopScreenBuyList);
    }
    else if (g_wKeysPressed & KeyUp)
    {
        MoveShopCategoryCursor(g_FredAndGeorgesShop.bCursor != 0 ? g_FredAndGeorgesShop.bCursor - 1 : 6);
        PlaySoundById(0);
    }
    else if (g_wKeysPressed & KeyDown)
    {
        MoveShopCategoryCursor(g_FredAndGeorgesShop.bCursor != 6 ? g_FredAndGeorgesShop.bCursor + 1 : 0);
        PlaySoundById(0);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        g_FredAndGeorgesShop.bCursor = 0;
        StartShopScreenTransition(ShopScreenMainMenu);
    }
}
