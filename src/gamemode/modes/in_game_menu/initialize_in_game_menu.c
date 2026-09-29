#include "types.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"

void InitializeInGameMenu(void)
{
    SetAlphaBlendTargets(0, 0);
    g_GameModeStackContext.dwModeState = 2;
    g_GameModeStackContext.dwModeScratchB =
        (g_PrevGameModeStackContext.dwCurrentGameMode == GameSave) ? g_ListMenuState.bInGameMenuCursor : 0;
    sub_08031FB8(1);
    BuildListMenu(&g_InGameMenuDefinition);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
