#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "main_menu.h"
#include "mem.h"
#include "minigame_menu.h"
#include "wizard_cracker_pop_it.h"

void ExitWizardCrackerPopItMinigame(void)
{
    s32 i;

    if (g_dwWizardCrackerPopItForceOverworldExit != 0)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
    }

    PlayScreenTransitionOutByIndex(0x3F, 2);

    for (i = 0; i < 5; i++)
    {
        sub_08030960(g_aWizardCrackerPopItPalettes[i].bSlotB);
        sub_08030960(g_aWizardCrackerPopItPalettes[i].bSlotA);
    }

    sub_0800D2DC();
    sub_0801DC6C(g_pWizardCrackerPopIt->pObject0);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    sub_0803171C();
    FreeBlock(g_pWizardCrackerPopIt);
    sub_0802CDB8();
}
