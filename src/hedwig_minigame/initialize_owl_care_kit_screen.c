#include "types.h"
#include "background.h"
#include "modes.h"
#include "save.h"
#include "sound.h"
#include "font.h"
#include "hedwig_minigame.h"
#include "gen/graphics/minigames/owl_care.h"
#include "screen_transitions.h"
#include "mem.h"
#include "game_state.h"

void InitializeOwlCareKitScreen(void)
{
    u32 bgControl;

    memset(&g_OwlCareKitScreen, 0, sizeof(OwlCareKitScreenState));
    g_GameModeStackContext.dwModeState = 0;

    if (!(g_saveStateBlock.owlCareKit.bFlags & OwlCareKitFlagVisited))
        ResetOwlCareKit();

    g_OwlCareKitScreen.abShownMeters[0] = 250;
    g_OwlCareKitScreen.abShownMeters[1] = 250;
    g_OwlCareKitScreen.abShownMeters[2] = 250;
    g_OwlCareKitScreen.bUnused = 0;
    g_OwlCareKitScreen.bMetersRedrawn = 0;
    g_OwlCareKitScreen.nUnused = 0;
    g_OwlCareKitScreen.bDroppingCount = 0;
    g_OwlCareKitScreen.bPanel = OwlCareKitPanelNone;
    g_OwlCareKitScreen.bShownSelection = 5;
    g_GameModeStackContext.dwModeScratchB = 0;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    bgControl = g_dwOwlCareBg0Control;
    SetTextTargetFromBgControl(bgControl);
    SetBgControl(3, g_dwOwlCareBg3Control);
    g_BgState.aLayers[3].pTilemap = LoadBgGraphic(3, gOwlCareGraphic001, 0, 0, 0, 0);
    SetBgControl(2, g_dwOwlCareBg2Control);
    CopyBgTilemapRectByCell(2, g_BgState.aLayers[3].pTilemap, 0, 0, 0, 0, 0, 0, 30, 20);
    SetBgControl(1, g_dwOwlCareBg1Control);
    LoadBgGraphic(1, gOwlCareGraphic002, 0x28, 0, 0, 0);
    SetBgControl(0, bgControl);

    g_GameModeStackContext.dwModeSubState = 0x10;
    g_OwlCareKitScreen.nBlendStep = 1;
    g_OwlCareKitScreen.bBgTimer = 0;
    SetAlphaBlendTargets(4, 8);
    SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 0x10 - g_GameModeStackContext.dwModeSubState);
    SpawnOwlCareKitActors();
    UpdateOwlDroppings();
    PlayMusicModule(0x15);
    UpdateOwlCareKitPanel();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
