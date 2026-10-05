#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

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
    sub_08007464(1, 0x6F);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    ResetPaletteAnimations();
}
