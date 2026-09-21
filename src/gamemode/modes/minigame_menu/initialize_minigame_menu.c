#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "main_menu.h"
#include "minigame_menu.h"
#include "object.h"

void InitializeMinigameMenu(void)
{
    ObjectFlagsD3 *pFlagsD3;

    sub_0801DF6C(0xA4A, 4, 0, NULL, 0, 0);
    pFlagsD3 = (ObjectFlagsD3 *)&g_pMenuCursorObject->bAffineFlagsHigh;
    pFlagsD3->bXFlip = 1;
    sub_0801DCC4(g_pMenuCursorObject, g_GameModeStackContext.dwCurrentGameModeArg2 * 0x20 + 0x48, 0x70);
    SetBgControl_candidate(1, g_dwMinigameMenuBg1Control);
    SetBgControl_candidate(3, g_dwMinigameMenuBg3Control);

    if (g_PrevGameModeCtx.dwCurrentGameMode == DivinationTeaMinigame)
        PlayMusicModule(0x21);

    DrawMinigameSelectMenu();
    HandleMinigameMenuSelection(g_GameModeStackContext.dwCurrentGameModeArg2);
    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
    g_GameModeStackContext.dwModeState_candidate = 0;
}
