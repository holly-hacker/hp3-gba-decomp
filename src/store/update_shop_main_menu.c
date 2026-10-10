#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "input.h"
#include "overworld/room.h"
#include "shop.h"

void UpdateShopMainMenu(void)
{
    if (g_wKeysPressed & KeyA)
    {
        g_FredAndGeorgesShop.pCursor->oam.objMode = 1;
        switch (g_FredAndGeorgesShop.bCursor)
        {
        case 0:
            PlaySoundById(1);
            g_FredAndGeorgesShop.bCategory = 0;
            StartShopScreenTransition(ShopScreenCategories);
            break;
        case 1:
            PlaySoundById(1);
            StartShopScreenTransition(ShopScreenSellList);
            break;
        case 2:
            PlaySoundById(2);
            PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
            break;
        }
    }
    else if (g_wKeysPressed & KeyUp)
    {
        MoveShopMainMenuCursor(g_FredAndGeorgesShop.bCursor != 0 ? g_FredAndGeorgesShop.bCursor - 1 : 2);
        PlaySoundById(0);
    }
    else if (g_wKeysPressed & KeyDown)
    {
        MoveShopMainMenuCursor(g_FredAndGeorgesShop.bCursor != 2 ? g_FredAndGeorgesShop.bCursor + 1 : 0);
        PlaySoundById(0);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
    }
}
