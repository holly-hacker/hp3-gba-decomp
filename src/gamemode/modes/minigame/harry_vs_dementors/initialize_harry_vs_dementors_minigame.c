#include "types.h"
#include "audio.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "harry_vs_dementors.h"
#include "text.h"

void InitializeHarryVsDementorsMinigame(void)
{
    u32 bgControl;

    g_HarryVsDementors.dwEventTimer60 = 0;
    g_HarryVsDementors.dwHideTimer5C = 0;
    g_HarryVsDementors.pCursorObject = NULL;
    g_GameModeStackContext.dwModeState = HarryVsDementorsStatePlaying;
    g_HarryVsDementors.dwUnk48 = 1;
    g_GameModeStackContext.dwModeTimer = 20;
    g_HarryVsDementors.bUnk4C = 3;
    g_HarryVsDementors.dwUnk44 = 0;
    g_HarryVsDementors.dwUnk50 = 0;
    g_HarryVsDementors.dwUnk58 = 0;
    g_HarryVsDementors.dwUnk2C = 1;
    g_HarryVsDementors.dwUnk40 = -1;
    g_HarryVsDementors.bUnk54 = 0;

    g_HarryVsDementors.pObject18 = SpawnObject(0, 0x78, 0x78, g_HarryVsDementorsObject18SpawnData);
    g_HarryVsDementors.pObject18->dwFlags &= ~ObjectFlagVisible;
    g_HarryVsDementors.pObject1C = SpawnObject(0, 0x78, 0x78, g_HarryVsDementorsObject1CSpawnData);
    g_HarryVsDementors.pObject1C->dwFlags &= ~ObjectFlagVisible;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwHarryVsDementorsBg0Control);
    bgControl = g_dwHarryVsDementorsBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetTextTargetFromBgControl(bgControl);

    switch (g_GameModeStackContext.dwCurrentGameModeArg3)
    {
    case 0:
        LoadBgGraphic(0, g_HarryVsDementorsBgGraphicA, 1, 0, 0, 0);
        break;
    case 1:
        LoadBgGraphic(0, g_HarryVsDementorsBgGraphicA, 1, 0, 0, 0);
        break;
    case 2:
        LoadBgGraphic(0, g_HarryVsDementorsBgGraphicB, 1, 0, 0, 0);
        break;
    }

    sub_0801EFA0();
    sub_0801EF48();
    sub_0801F108();
    sub_0801E414();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0x1E);
}
