#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "input.h"
#include "hw/mem.h"
#include "menu/connectivity.h"
#include "menu/in_game_menu.h"

void HandleConnectivityMenuTick(void)
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
            SelectInGameMenuEntry_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_GameModeStackContext.dwModeSubState = 0;
            g_GameModeStackContext.dwModeState = 4;
            g_GameModeStackContext.dwCurrentGameModeArg2 = -1;
        }
        break;

    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            if (g_GameModeStackContext.dwCurrentGameModeArg2 == -1)
            {
                PushGameMode(InGameMenuFadeIn);
            }
            else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0)
            {
                PushGameMode(g_ConnectivityMenu.pEntries[g_GameModeStackContext.dwModeScratchB].mode);
            }
            else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 1)
            {
                ClearBgTilemap(2);
                FreeAllObjects(&g_ActiveObjectListState.pHead);
                g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
                StartMenuOverlayFadeOut();
            }
        }
        break;
    }
}
