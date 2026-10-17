#include "types.h"
#include "modes.h"
#include "pause_menu.h"
#include "screen_transitions.h"

void InitializeInGameMenu(void)
{
    SetAlphaBlendTargets(0, 0);
    g_GameModeStackContext.dwModeState = 2;
    g_GameModeStackContext.dwModeScratchB =
        (g_PrevGameModeStackContext.dwCurrentGameMode == GameSave) ? g_ListMenuState.bInGameMenuCursor : 0;
    BeginPauseMenuScreen(1);
    BuildListMenu(&g_InGameMenuDefinition);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
