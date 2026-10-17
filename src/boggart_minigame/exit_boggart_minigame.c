#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "minigame_menu.h"
#include "boggart_minigame.h"
#include "cursor.h"
#include "minigame_difficulty_select.h"
#include "sound.h"
#include "screen_transitions.h"

void ExitBoggartMinigame(void)
{
    if (g_BoggartMinigame.dwExitToMenu == 1)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    }

    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_BoggartMinigame.pCursorActor != NULL)
    {
        ReleaseMenuCursor(g_BoggartMinigame.pCursorActor);
        g_BoggartMinigame.pCursorActor = NULL;
        FreeAllParticles();
    }

    FreeMinigameTextPanel(g_BoggartMinigame.pScorePanel);
    FreeMinigameTextPanel(g_BoggartMinigame.pLivesPanel);
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
    SyncSaveOptionsPausingKrawall();
}
