#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "game_save.h"
#include "in_game_menu.h"
#include "input.h"
#include "items_menu.h"
#include "main_menu.h"

void UpdateItemsSectionSelect(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            SetItemsItemSelectFilter(g_aItemsSectionFilters[g_GameModeStackContext.dwModeScratchB]);
            g_ItemsSectionSelectNextMode = ItemsItemSelect;
            g_GameModeStackContext.dwModeState = 3;
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_ItemsSectionSelectNextMode = InGameMenuFadeIn;
            g_GameModeStackContext.dwModeState = 3;
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            sub_0803227C();
        }
        break;

    case 3:
        sub_080321A8();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(g_ItemsSectionSelectNextMode);
        break;
    }
}
