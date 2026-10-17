#include "background.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "actor.h"
#include "pscreen_connectivity.h"
#include "pause_menu.h"

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
                FreeAllActors(&g_ActiveActorListState.pHead);
                g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
                StartMenuOverlayFadeOut();
            }
        }
        break;
    }
}
