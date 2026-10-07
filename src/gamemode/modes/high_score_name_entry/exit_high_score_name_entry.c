#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/main_menu.h"
#include "minigame/high_score_name_entry.h"

void ExitHighScoreNameEntry(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_HighScoreNameEntry.pCursor);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 2;
    FreeAllParticles();
}
