#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "input.h"
#include "hw/mem.h"
#include "menu/connectivity.h"
#include "menu/in_game_menu.h"
#include "menu/status_equip.h"

void UpdateConfirmTradeScreen(void)
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
        {
            StartMenuFadeOut();
            g_GameModeStackContext.dwModeState = 4;
            if (g_wKeysPressed & KeyB)
            {
                PlaySoundById(2);
                g_GameModeStackContext.dwModeScratchB = 0;
            }
            else
                PlaySoundById(1);
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        break;

    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            if (g_GameModeStackContext.dwModeScratchB == 0)
            {
                ClearBgTilemap(2);
                FreeAllObjects(&g_ActiveObjectListState.pHead);
                PushGameMode(Connectivity);
            }
            else if (g_GameModeStackContext.dwModeScratchB == 1)
            {
                ClearBgTilemap(2);
                FreeAllObjects(&g_ActiveObjectListState.pHead);
                PushGameMode(CardTrade);
            }
        }
        break;
    }
}
