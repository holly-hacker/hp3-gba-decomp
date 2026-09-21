#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "in_game_menu.h"

void InitializeInGameMenu(void)
{
    SetAlphaBlendTargets(0, 0);
    g_GameModeStackContext.dwModeState = 2;
    g_GameModeStackContext.dwModeScratchB =
        (g_PrevGameModeCtx.dwCurrentGameMode == GameSave) ? g_bInGameMenuCursor : 0;
    sub_08031FB8(1);
    BuildListMenu_candidate(g_InGameMenuDefinition);
    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
}
