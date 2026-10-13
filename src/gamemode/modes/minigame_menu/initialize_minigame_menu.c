#include "types.h"
#include "background.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"
#include "actor.h"

void InitializeMinigameMenu(void)
{

    InitializeMenuScreen(0xA4A, 4, 0, NULL, 0, 0);
    g_pMenuCursorActor->oam.hFlip = 1;
    SetMenuCursorPosition(g_pMenuCursorActor, g_GameModeStackContext.dwCurrentGameModeArg2 * 0x20 + 0x48, 0x70);
    SetBgControl(1, g_dwMinigameMenuBg1Control);
    SetBgControl(3, g_dwMinigameMenuBg3Control);

    if (g_PrevGameModeStackContext.dwCurrentGameMode == DivinationTeaMinigame)
        PlayMusicModule(0x21);

    DrawMinigameSelectMenu();
    HandleMinigameMenuSelection(g_GameModeStackContext.dwCurrentGameModeArg2);
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwModeState = 0;
}
