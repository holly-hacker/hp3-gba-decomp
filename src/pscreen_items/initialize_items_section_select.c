#include "modes.h"
#include "pause_menu.h"
#include "pscreen_items.h"

void InitializeItemsSectionSelect(void)
{
    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeScratchB = g_bItemsSectionCursor;
    StartMenuFadeIn();
    BuildListMenu(&g_ItemsSectionMenuDefinition);
}
