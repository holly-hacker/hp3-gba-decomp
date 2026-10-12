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

    FreeMinigameTextPanel(g_HarryVsDementors.pTextPanel20);
    FreeMinigameTextPanel(g_HarryVsDementors.pTextPanel24);
    FreeMinigameTextPanel(g_HarryVsDementors.pTextPanel28);
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
}
