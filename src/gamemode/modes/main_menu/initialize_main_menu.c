#include "types.h"
#include "graphics/audio.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "menu/main_menu.h"
#include "graphics/text.h"
#include "gen/graphics/menus.h"

void InitializeMainMenu(void)
{
    ResetSaveStateForNewGame();
    ClearRoomObjectStateBuffer();

    // Arg2 is the entry to highlight first.
    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwModeScratchB = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_GameModeStackContext.dwModeSubState = 0;
    g_GameModeStackContext.dwModeTimer = 0;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_MainMenuState.dwLoadGameAvailable = HasLoadableSaveSlot();

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwMainMenuBg3Control);
    LoadBgGraphic(3, gMenuBg3Graphic, 0, 0, 0, 0);
    SetBgScrollX_candidate(3, 0x80000);
    SetBgControlRegister_candidate(2, g_dwMainMenuBg2Control);
    ClearBgTilemap(2);
    LoadBgGraphic(2, gMainMenuBg2Graphic, 1, 0, 1, 1);
#ifndef VERSION_JP
    LoadBgGraphic(2, g_apMainMenuTitleGraphic[GetLanguage()], 0xC8, 0, 0xF, 9);
#endif
    SetBgControlRegister_candidate(1, g_dwMainMenuBg1Control);
    ClearBgTilemap(1);
    ClearResourceCacheSlots();
    sub_0803094C(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    StartMainMenuPaletteEffect_candidate();

    PlayMusicModule(0x21);
    PlayScreenTransitionInByIndex(0x3F, 2);
    SetAlphaBlendTargets(4, 8);
    SetAlphaBlendCoefficients(0, 0x10);
    EnableBg(2);
}
