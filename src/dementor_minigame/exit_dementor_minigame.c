#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "dementor_minigame.h"
#include "menu/main_menu.h"
#include "mem.h"
#include "actor.h"
#include "menu/minigame_menu.h"
#include "cursor.h"

void ExitDementorMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_DementorMinigame.pCursorActor != NULL)
    {
        ReleaseMenuCursor(g_DementorMinigame.pCursorActor);
        g_DementorMinigame.pCursorActor = NULL;
        FreeAllParticles();
    }

    FreeMinigameTextPanel(g_DementorMinigame.pScorePanel);
    FreeMinigameTextPanel(g_DementorMinigame.pLivesPanel);
    FreeMinigameTextPanel(g_DementorMinigame.pMissesPanel);
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
}
