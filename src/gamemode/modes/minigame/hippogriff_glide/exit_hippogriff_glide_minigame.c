#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "hippogriff_glide.h"
#include "mem.h"
#include "minigame_menu.h"

void ExitHippogriffGlideMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_08030960(0);
    sub_0802D6B8();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800A914();

    if (g_GameModeStackContext.dwCurrentGameModeArg3 != 2)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
    }

    FreeBlock(g_pHippogriffGlide);
    sub_0802CDB8();
}
