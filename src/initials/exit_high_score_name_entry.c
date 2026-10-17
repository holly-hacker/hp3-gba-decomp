#include "types.h"
#include "graphics/display.h"
#include "particles.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "menu/main_menu.h"
#include "initials.h"
#include "cursor.h"

void ExitHighScoreNameEntry(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_HighScoreNameEntry.pCursor);
    FreeAllActors(&g_ActiveActorListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 2;
    FreeAllParticles();
}
