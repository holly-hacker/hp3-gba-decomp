#include "types.h"
#include "game_modes.h"
#include "main_menu.h"
#include "object.h"

void ShowMainMenuEntries_candidate(void)
{
    u32 entry;

    g_MainMenuState.pCursorObject = sub_0801D940(4);
    g_MainMenuState.pCursorObject->bField2To3_candidate = 1;
    g_MainMenuState.pCursorObject->bXFlip = 1;
    PositionMainMenuCursorObject_candidate(0);

    for (entry = 0; entry < 4; entry++)
    {
        if (entry == MainMenuLoadGame && !g_MainMenuState.dwLoadGameAvailable)
            continue;
        DrawMainMenuEntry_candidate(entry, g_GameModeStackContext.dwModeScratchB);
    }
}
