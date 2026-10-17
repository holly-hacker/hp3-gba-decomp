#include "sound.h"
#include "modes.h"
#include "pause_menu.h"
#include "input.h"
#include "pscreen_items.h"

void UpdateItemsSectionSelect(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
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
            MoveListMenuCursor();
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(g_ItemsSectionSelectNextMode);
        break;
    }
}
