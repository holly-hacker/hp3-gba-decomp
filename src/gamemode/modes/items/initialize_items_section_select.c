#include "types.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"
#include "menu/items_menu.h"

void InitializeItemsSectionSelect(void)
{
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeScratchB = g_bItemsSectionCursor;
    StartMenuFadeIn();
    BuildListMenu(&g_ItemsSectionMenuDefinition);
}
