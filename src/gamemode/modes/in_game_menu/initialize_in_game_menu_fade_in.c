#include "types.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"

void InitializeInGameMenuFadeIn(void)
{
    if (g_PrevGameModeStackContext.dwCurrentGameMode == StatusEquipCharacterSelect)
        sub_080323B0();

    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeScratchB = g_ListMenuState.bInGameMenuCursor;
    sub_080320A4();
    BuildListMenu(&g_InGameMenuDefinition);
    sub_0803233C();
}
