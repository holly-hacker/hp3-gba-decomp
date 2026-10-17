#include "types.h"
#include "background.h"
#include "sound.h"
#include "modes.h"
#include "boggart_minigame.h"
#include "font.h"
#include "screen_transitions.h"
#include "gen/graphics/minigames/boggart.h"

void InitializeBoggartMinigame(void)
{
    u32 bgControl;

    ClearObjPaletteSlots();
    g_BoggartMinigame.dwExitToMenu = 0;
    g_BoggartMinigame.pCursorActor = NULL;
    g_BoggartMinigame.dwBoggartDirection = -1;
    g_GameModeStackContext.dwModeState = BoggartMinigameStateIntro;
    g_BoggartMinigame.dwCountdown = 3;
    g_BoggartMinigame.bLives = 3;
    g_BoggartMinigame.pCastEffectActor = NULL;
    g_BoggartMinigame.dwScore = 0;
    g_BoggartMinigame.bRound = 0;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwBoggartMinigameBg0Control);
    bgControl = g_dwBoggartMinigameBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetTextTargetFromBgControl(bgControl);
    LoadBgGraphic(0, gBoggartBgGraphic, 1, 0, 0, 0);

    DrawBoggartMinigameScore();
    DrawBoggartMinigameLives();
    SpawnBoggartMinigameActors();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0xE);
}
