#include "types.h"
#include "background.h"
#include "color.h"
#include "sound.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "modes.h"
#include "particles.h"
#include "save.h"
#include "game_state.h"
#include "map.h"
#include "title.h"
#include "text.h"
#include "gen/graphics/menus.h"
#include "screen_transitions.h"
#ifdef VERSION_JP
#include "gen/graphics/menus/jp.h"
#else
#include "gen/graphics/menus/us.h"
#endif

void InitializeMainMenu(void)
{
    ResetSaveStateForNewGame();
    ClearRoomActorStateBuffer();

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
    SetBgScrollFixedX(3, 0x80000);
    SetBgControlRegister(2, g_dwMainMenuBg2Control);
    ClearBgTilemap(2);
    LoadBgGraphic(2, gMainMenuBg2Graphic, 1, 0, 1, 1);
#ifndef VERSION_JP
    LoadBgGraphic(2, g_apMainMenuTitleGraphic[GetLanguage()], 0xC8, 0, 0xF, 9);
#endif
    SetBgControlRegister(1, g_dwMainMenuBg1Control);
    ClearBgTilemap(1);
    ClearObjPaletteSlots();
    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    StartMainMenuPaletteEffect();

    PlayMusicModule(0x21);
    PlayScreenTransitionInByIndex(0x3F, 2);
    SetAlphaBlendTargets(4, 8);
    SetAlphaBlendCoefficients(0, 0x10);
    EnableBg(2);
}
