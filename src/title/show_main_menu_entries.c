#include "types.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "title.h"
#include "actor.h"
#include "cursor.h"

void ShowMainMenuEntries(void)
{
    u32 entry;

    g_MainMenuState.pCursorActor = SpawnMenuCursorActor(4);
    g_MainMenuState.pCursorActor->oam.objMode = 1;
    g_MainMenuState.pCursorActor->oam.hFlip = 1;
    PositionMainMenuCursorActor(0);

    for (entry = 0; entry < 4; entry++)
    {
        if (entry == MainMenuLoadGame && !g_MainMenuState.dwLoadGameAvailable)
            continue;
        DrawMainMenuEntry(entry, g_GameModeStackContext.dwModeScratchB);
    }
}
