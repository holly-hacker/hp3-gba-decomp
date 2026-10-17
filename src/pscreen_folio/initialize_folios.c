#include "types.h"
#include "graphics/display.h"
#include "modes.h"
#include "pscreen_folio.h"
#include "pause_menu.h"
#include "screen_transitions.h"

void InitializeFolios(void)
{
    g_GameModeStackContext.dwModeScratchB = g_bFoliosMenuCursor;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
    {
        g_GameModeStackContext.dwModeState = 2;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_FoliosMenuDefinition);
        PlayScreenTransitionInByIndex(0x3F, 2);
    }
    else
    {
        g_GameModeStackContext.dwModeState = 1;
        StartMenuFadeIn();
        BuildListMenu(&g_FoliosMenuDefinition);
    }
}
