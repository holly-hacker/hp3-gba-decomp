#include "modes.h"
#include "pause_menu.h"

void InitializeInGameMenuFadeIn(void)
{
    if (g_PrevGameModeStackContext.dwCurrentGameMode == StatusEquipCharacterSelect)
        NoopStatusEquipReturned();

    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeScratchB = g_ListMenuState.bInGameMenuCursor;
    StartMenuFadeIn();
    BuildListMenu(&g_InGameMenuDefinition);
    DrawPauseMenuObjective();
}
