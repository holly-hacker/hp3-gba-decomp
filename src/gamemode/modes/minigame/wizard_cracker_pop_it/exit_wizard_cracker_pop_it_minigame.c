#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"
#include "minigame/wizard_cracker_pop_it.h"

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
        sub_08030960(g_aWizardCrackerPopItPalettes[i].bSlotB);
        sub_08030960(g_aWizardCrackerPopItPalettes[i].bSlotA);
    }

    ResetPaletteAnimations();
    ReleaseMenuCursor(g_pWizardCrackerPopIt->pObject0);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    FreeAllParticles();
    FreeBlock(g_pWizardCrackerPopIt);
    sub_0802CDB8();
}
