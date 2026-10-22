#include "modes.h"
#include "actor.h"
#include "boggart_minigame.h"
#include "cursor.h"
#include "minigame_high_score.h"
#include "sound.h"
#include "screen_transitions.h"
#include "map.h"

void ExitBoggartMinigame(void)
{
    if (g_BoggartMinigame.dwExitToMenu == 1)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = OverworldEntryReturn;
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
    StopAllSoundEffects();
    SyncSaveOptionsPausingKrawall();
}
