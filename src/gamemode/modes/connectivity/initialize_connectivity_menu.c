#include "types.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/save.h"
#include "hw/mem.h"
#include "menu/connectivity.h"
#include "menu/in_game_menu.h"

void InitializeConnectivityMenu(void)
{
    g_GameModeStackContext.dwModeScratchB = g_bConnectivityMenuCursor;
    CopyMemory(&g_ConnectivityMenu, &g_ConnectivityMenuTemplate, sizeof(ListMenuDefinition));

    if (g_saveManager.header.bHeaderFlags.all & flOwlCareKitUnlocked)
    {
        if ((g_saveStateBlock.owlCareKit.bFlags & 1) == 0)
            g_ConnectivityMenu.pEntries = g_aConnectivityOwlNameEntries;
        else
            g_ConnectivityMenu.pEntries = g_aConnectivityOwlCareEntries;
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
    {
        g_GameModeStackContext.dwModeState = 2;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_ConnectivityMenu);
        PlayScreenTransitionInByIndex(0x3F, 2);
    }
    else
    {
        g_GameModeStackContext.dwModeState = 1;
        StartMenuFadeIn();
        BuildListMenu(&g_ConnectivityMenu);
    }
}
