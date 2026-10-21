#include "types.h"
#include "color.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "pop_it_minigame.h"
#include "cursor.h"
#include "minigame_high_score.h"
#include "screen_transitions.h"

void ExitWizardCrackerPopItMinigame(void)
{
    s32 i;

    if (g_dwWizardCrackerPopItForceOverworldExit != 0)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    }

    PlayScreenTransitionOutByIndex(0x3F, 2);

    for (i = 0; i < ARRAY_COUNT(g_aWizardCrackerPopItPalettes); i++)
    {
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bSelectedSlot);
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bIdleSlot);
    }

    ResetPaletteAnimations();
    ReleaseMenuCursor(g_pWizardCrackerPopIt->pCursor);
    FreeAllActors(&g_ActiveActorListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    FreeAllParticles();
    FreeBlock(g_pWizardCrackerPopIt);
    SyncSaveOptionsPausingKrawall();
}
