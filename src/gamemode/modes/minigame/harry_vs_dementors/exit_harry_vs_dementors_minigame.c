#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "minigame/harry_vs_dementors.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"

void ExitHarryVsDementorsMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_HarryVsDementors.pCursorActor != NULL)
    {
        ReleaseMenuCursor(g_HarryVsDementors.pCursorActor);
        g_HarryVsDementors.pCursorActor = NULL;
        FreeAllParticles();
    }

    sub_0802CEE4(g_HarryVsDementors.pActorGroup20);
    sub_0802CEE4(g_HarryVsDementors.pActorGroup24);
    sub_0802CEE4(g_HarryVsDementors.pActorGroup28);
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
}
