#include "types.h"
#include "game_modes.h"
#include "in_game_menu.h"
#include "items_menu.h"

void InitializeItemsSectionSelect(void)
{
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeScratchB = g_bItemsSectionCursor;
    sub_080320A4();
    BuildListMenu(&g_ItemsSectionMenuDefinition);
}
