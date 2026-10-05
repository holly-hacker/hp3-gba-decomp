#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "minigame/riddikulus.h"
#include "graphics/text.h"

void InitializeRiddikulusMinigame(void)
{
    u32 bgControl;

    ClearResourceCacheSlots();
    g_Riddikulus.dwExitToMenu = 0;
    g_Riddikulus.pCursorObject = NULL;
    g_Riddikulus.dwUnk24 = -1;
    g_GameModeStackContext.dwModeState = RiddikulusStateIntro;
    g_Riddikulus.dwCountdown = 3;
    g_Riddikulus.bUnk34 = 3;
    g_Riddikulus.dwUnk14 = 0;
    g_Riddikulus.dwScore = 0;
    g_Riddikulus.bUnk35 = 0;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwRiddikulusBg0Control);
    bgControl = g_dwRiddikulusBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetTextTargetFromBgControl(bgControl);
    LoadBgGraphic(0, gRiddikulusBgGraphic, 1, 0, 0, 0);

    sub_08008B84();
    sub_08008BD8();
    sub_08008360();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0xE);
}
