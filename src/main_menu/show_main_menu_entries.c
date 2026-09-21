#include "types.h"
#include "game_modes.h"
#include "main_menu.h"
#include "object.h"

void ShowMainMenuEntries_candidate(void)
{
    ObjectFlagsD1 *pFlags;
    ObjectFlagsD3 *pFlagsD3;
    u32 entry;

    g_MainMenuState.pCursorObject = sub_0801D940(4);
    pFlags = (ObjectFlagsD1 *)&g_MainMenuState.pCursorObject->bFlags_0xD1;
    pFlags->bField2To3_candidate = 1;
    pFlagsD3 = (ObjectFlagsD3 *)&g_MainMenuState.pCursorObject->bAffineFlagsHigh;
    pFlagsD3->bXFlip = 1;
    PositionMainMenuCursorObject_candidate(0);

    for (entry = 0; entry < 4; entry++)
    {
        if (entry == MainMenuLoadGame && !g_MainMenuState.dwLoadGameAvailable)
            continue;
        DrawMainMenuEntry_candidate(entry, g_GameModeStackContext.dwModeScratchB_candidate);
    }
}
