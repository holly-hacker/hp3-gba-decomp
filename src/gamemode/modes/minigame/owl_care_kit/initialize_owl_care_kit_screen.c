#include "types.h"
#include "game/game_modes.h"
#include "game/save.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "font.h"
#include "minigame/owlcare.h"
#include "gen/graphics/minigames/owl_care.h"

extern void *memset(void *dest, int value, u32 size);

void InitializeOwlCareKitScreen(void)
{
    u32 bgControl;

    memset(&g_OwlCareKitScreen, 0, sizeof(OwlCareKitScreenState));
    g_GameModeStackContext.dwModeState = 0;

    if (!(g_saveStateBlock.owlCareKit.bFlags & 1))
        sub_08023188();

    g_OwlCareKitScreen.abUnkD4[0] = 250;
    g_OwlCareKitScreen.abUnkD4[1] = 250;
    g_OwlCareKitScreen.abUnkD4[2] = 250;
    g_OwlCareKitScreen.bUnkDC = 0;
    g_OwlCareKitScreen.bUnkDD = 0;
    g_OwlCareKitScreen.dwUnkD8 = 0;
    g_OwlCareKitScreen.bUnkDF = 0;
    g_OwlCareKitScreen.bUnkDE = 0;
    g_OwlCareKitScreen.bUnkE0 = 5;
    g_GameModeStackContext.dwModeScratchB = 0;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    bgControl = g_dwOwlCareBg0Control;
    SetTextTargetFromBgControl(bgControl);
    SetBgControl(3, g_dwOwlCareBg3Control);
    g_aBgScrollState[3].pBgGraphicResult_candidate = LoadBgGraphic(3, gOwlCareGraphic001, 0, 0, 0, 0);
    SetBgControl(2, g_dwOwlCareBg2Control);
    sub_08006A98(2, g_aBgScrollState[3].pBgGraphicResult_candidate, 0, 0, 0, 0, 0, 0, 30, 20);
    SetBgControl(1, g_dwOwlCareBg1Control);
    LoadBgGraphic(1, gOwlCareGraphic002, 0x28, 0, 0, 0);
    SetBgControl(0, bgControl);

    g_GameModeStackContext.dwModeSubState = 0x10;
    g_OwlCareKitScreen.bUnkE5 = 1;
    g_OwlCareKitScreen.bUnkE6 = 0;
    SetAlphaBlendTargets(4, 8);
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 0x10 - g_GameModeStackContext.dwModeSubState);
    sub_0802246C();
    sub_08022B40();
    PlayMusicModule(0x15);
    sub_08021E80();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
