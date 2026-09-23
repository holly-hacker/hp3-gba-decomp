#include "types.h"
#include "game_modes.h"
#include "game_save.h"
#include "in_game_menu.h"
#include "input.h"

void UpdateItemUseScreen(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & (KeyA | KeyB))
            g_GameModeStackContext.dwModeState = 3;
        break;

    case 3:
        sub_080321A8();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(ItemsItemSelect);
        break;
    }
}
