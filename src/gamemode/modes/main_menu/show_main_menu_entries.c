#include "types.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "graphics/object.h"

void ShowMainMenuEntries(void)
{
    u32 entry;

    g_MainMenuState.pCursorObject = SpawnMenuCursorObject(4);
    g_MainMenuState.pCursorObject->oam.objMode = 1;
    g_MainMenuState.pCursorObject->oam.hFlip = 1;
    PositionMainMenuCursorObject_candidate(0);

    for (entry = 0; entry < 4; entry++)
    {
        if (entry == MainMenuLoadGame && !g_MainMenuState.dwLoadGameAvailable)
            continue;
        DrawMainMenuEntry(entry, g_GameModeStackContext.dwModeScratchB);
    }
}
