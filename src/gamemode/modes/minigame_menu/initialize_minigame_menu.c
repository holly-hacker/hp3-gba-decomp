#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "main_menu.h"
#include "minigame_menu.h"
#include "object.h"

void InitializeMinigameMenu(void)
{

    sub_0801DF6C(0xA4A, 4, 0, NULL, 0, 0);
    g_pMenuCursorObject->oam.hFlip = 1;
    sub_0801DCC4(g_pMenuCursorObject, g_GameModeStackContext.dwCurrentGameModeArg2 * 0x20 + 0x48, 0x70);
    SetBgControl(1, g_dwMinigameMenuBg1Control);
    SetBgControl(3, g_dwMinigameMenuBg3Control);

    if (g_PrevGameModeStackContext.dwCurrentGameMode == DivinationTeaMinigame)
        PlayMusicModule(0x21);

    DrawMinigameSelectMenu();
    HandleMinigameMenuSelection(g_GameModeStackContext.dwCurrentGameModeArg2);
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwModeState = 0;
}
