#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "boggart_minigame.h"
#include "font.h"

void InitializeBoggartMinigame(void)
{
    u32 bgControl;

    ClearObjPaletteSlots();
    g_BoggartMinigame.dwExitToMenu = 0;
    g_BoggartMinigame.pCursorActor = NULL;
    g_BoggartMinigame.dwUnk24 = -1;
    g_GameModeStackContext.dwModeState = BoggartMinigameStateIntro;
    g_BoggartMinigame.dwCountdown = 3;
    g_BoggartMinigame.bUnk34 = 3;
    g_BoggartMinigame.dwUnk14 = 0;
    g_BoggartMinigame.dwScore = 0;
    g_BoggartMinigame.bUnk35 = 0;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwBoggartMinigameBg0Control);
    bgControl = g_dwBoggartMinigameBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetTextTargetFromBgControl(bgControl);
    LoadBgGraphic(0, gBoggartBgGraphic, 1, 0, 0, 0);

    sub_08008B84();
    sub_08008BD8();
    sub_08008360();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0xE);
}
