#include "types.h"
#include "game/game_modes.h"
#include "gen/graphics/menus.h"
#include "graphics/display.h"
#include "font.h"
#include "menu/menu.h"
#include "menu/owl_name_select.h"

void InitializeOwlNameSelect(void)
{
    u32 bg2Control;

    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
    g_GameModeStackContext.dwModeScratchA = 0;
    g_GameModeStackContext.dwModeState = 0;

    DisableBg(2);
    bg2Control = g_dwCommonBg2Control;
    SetBgControlRegister_candidate(2, bg2Control);
    ClearBgTilemap(2);

    g_GameModeStackContext.dwModeSubState = 0x10;
    SetAlphaBlendTargets(8, 3);
    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                              g_GameModeStackContext.dwModeSubState);

    SetBgControl(3, g_dwOwlNameSelectBg3Control);
    ClearBgTilemap(3);
    LoadBgGraphic(3, gDialogBackgrounds002, 0x2E9, 0, 0, 6);
    SetBgScroll_candidate(3, 8, 0);
    sub_08007434(0x1000);

    sub_08030594();
    SetTextTargetFromBgControl(bg2Control);
    sub_080305F0();
    sub_08030644();
}
