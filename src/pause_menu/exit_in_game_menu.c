#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "color.h"
#include "modes.h"
#include "pause_menu.h"
#include "mem.h"
#include "actor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void ExitInGameMenu(void)
{
    g_ListMenuState.bInGameMenuCursor = g_GameModeStackContext.dwModeScratchB;

    if (GetPendingGameMode_candidate() == Overworld)
    {
        SetScreenDarkenParams_candidate(0, 8);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        SetScreenDarkenParams_candidate(0, 8);
    }

    ExitMenuScreen();
    FillBgTilemapWithTile(1, 0x6F);
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetPaletteAnimations();
}
