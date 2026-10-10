#include "types.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "menu/in_game_menu.h"
#include "input.h"

void UpdateItemUseScreen(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & (KeyA | KeyB))
            g_GameModeStackContext.dwModeState = 3;
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(ItemsItemSelect);
        break;
    }
}
