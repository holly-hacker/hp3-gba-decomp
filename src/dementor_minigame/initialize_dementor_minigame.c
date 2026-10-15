#include "types.h"
#include "background.h"
#include "graphics/audio.h"
#include "actor.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "dementor_minigame.h"
#include "font.h"
#include "gen/graphics/overworld.h"

void InitializeDementorMinigame(void)
{
    u32 bgControl;

    g_DementorMinigame.dwEventTimer60 = 0;
    g_DementorMinigame.dwHideTimer5C = 0;
    g_DementorMinigame.pCursorActor = NULL;
    g_GameModeStackContext.dwModeState = DementorMinigameStatePlaying;
    g_DementorMinigame.dwUnk48 = 1;
    g_GameModeStackContext.dwModeTimer = 20;
    g_DementorMinigame.bUnk4C = 3;
    g_DementorMinigame.dwUnk44 = 0;
    g_DementorMinigame.dwUnk50 = 0;
    g_DementorMinigame.dwUnk58 = 0;
    g_DementorMinigame.dwUnk2C = 1;
    g_DementorMinigame.dwUnk40 = -1;
    g_DementorMinigame.bUnk54 = 0;

    g_DementorMinigame.pActor18 = SpawnActor(0, 0x78, 0x78, (const ObjPalette *)gHarryVsDementorsActor18Palette);
    g_DementorMinigame.pActor18->dwFlags &= ~ActorFlagVisible;
    g_DementorMinigame.pActor1C = SpawnActor(0, 0x78, 0x78, (const ObjPalette *)gHarryVsDementorsActor1CPalette);
    g_DementorMinigame.pActor1C->dwFlags &= ~ActorFlagVisible;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDementorMinigameBg0Control);
    bgControl = g_dwDementorMinigameBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetTextTargetFromBgControl(bgControl);

    switch (g_GameModeStackContext.dwCurrentGameModeArg3)
    {
    case 0:
        LoadBgGraphic(0, gHarryVsDementorsBgGraphicA, 1, 0, 0, 0);
        break;
    case 1:
        LoadBgGraphic(0, gHarryVsDementorsBgGraphicA, 1, 0, 0, 0);
        break;
    case 2:
        LoadBgGraphic(0, gHarryVsDementorsBgGraphicB, 1, 0, 0, 0);
        break;
    }

    sub_0801EFA0();
    sub_0801EF48();
    sub_0801F108();
    sub_0801E414();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0x1E);
}
