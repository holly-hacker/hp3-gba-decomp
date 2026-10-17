#include "types.h"
#include "battle/battle.h"
#include "dementor_minigame.h"
#include "mem.h"
#include "actor.h"
#include "minigame_menu.h"
#include "cursor.h"
#include "minigame_difficulty_select.h"
#include "sound.h"
#include "screen_transitions.h"

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
