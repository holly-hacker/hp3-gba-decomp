#include "types.h"
#include "battle/battle.h"
#include "color.h"
#include "graphics/display.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "mem.h"
#include "actor.h"
#include "minigame_menu.h"
#include "pop_it_minigame.h"
#include "cursor.h"
#include "minigame_difficulty_select.h"

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
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bSlotB);
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bSlotA);
    }

    ResetPaletteAnimations();
    ReleaseMenuCursor(g_pWizardCrackerPopIt->pActor0);
    FreeAllActors(&g_ActiveActorListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    FreeAllParticles();
    FreeBlock(g_pWizardCrackerPopIt);
    SyncSaveOptionsPausingKrawall();
}
