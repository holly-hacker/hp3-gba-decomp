#include "types.h"
#include "audio.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "graphics.h"
#include "main_menu.h"
#include "text.h"

void InitializeMainMenu(void)
{
    ResetSaveStateForNewGame_candidate();
    sub_0802B0F4();

    // Arg2 is the entry to highlight first.
    g_GameModeStackContext.dwModeState_candidate = 0;
    g_GameModeStackContext.dwModeScratchB_candidate = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_GameModeStackContext.dwModeSubState_candidate = 0;
    g_GameModeStackContext.dwModeTimer_candidate = 0;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_MainMenuState.dwLoadGameAvailable = HasLoadableSaveSlot_candidate();

    ResetDisplayState_candidate(0);
    SetDispcntFlag(0x1000);
    SetBgControl_candidate(3, g_dwMainMenuBg3Control);
    LoadBgGraphic_candidate(3, g_MenuBg3Graphic, 0, 0, 0, 0);
    sub_08007B30(3, 0x80000);
    sub_080072EC(2, g_dwMainMenuBg2Control);
    ClearBgTilemap_candidate(2);
    LoadBgGraphic_candidate(2, g_MainMenuBg2Graphic, 1, 0, 1, 1);
    LoadBgGraphic_candidate(2, g_apMainMenuTitleGraphic[GetLanguage()], 0xC8, 0, 0xF, 9);
    sub_080072EC(1, g_dwMainMenuBg1Control);
    ClearBgTilemap_candidate(1);
    ClearResourceCacheSlots();
    sub_0803094C(0);
    sub_0800D264((void *)g_MainMenuPalette, 0, 0x10);
    sub_080438B4();

    PlayMusicModule(0x21);
    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
    SetAlphaBlendTargets(4, 8);
    SetAlphaBlendCoefficients(0, 0x10);
    EnableBg(2);
}
