#include "battle/battle.h"
#include "char_block.h"
#include "modes.h"
#include "buckbeak_minigame.h"
#include "mem.h"
#include "actor.h"
#include "minigame_difficulty_select.h"
#include "screen_transitions.h"

void ExitBuckbeakMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    UnreserveObjPaletteSlot(0);
    FreeFloorEffect();
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeBgTileAnimations();

    if (g_GameModeStackContext.dwCurrentGameModeArg3 != 2)
    {
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
    }

    FreeBlock(g_pBuckbeakMinigame);
    SyncSaveOptionsPausingKrawall();
}
