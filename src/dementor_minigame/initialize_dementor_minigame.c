#include "types.h"
#include "background.h"
#include "sound.h"
#include "actor.h"
#include "graphics/display.h"
#include "modes.h"
#include "dementor_minigame.h"
#include "font.h"
#include "gen/graphics/overworld.h"
#include "screen_transitions.h"

void InitializeDementorMinigame(void)
{
    u32 bgControl;

    g_DementorMinigame.dwSpellTimer = 0;
    g_DementorMinigame.dwSpellHideTimer = 0;
    g_DementorMinigame.pCursorActor = NULL;
    g_GameModeStackContext.dwModeState = DementorMinigameStatePlaying;
    g_DementorMinigame.dwStartDelay = 1;
    g_GameModeStackContext.dwModeTimer = 20;
    g_DementorMinigame.bLives = 3;
    g_DementorMinigame.dwScore = 0;
    g_DementorMinigame.dwRepelled = 0;
    g_DementorMinigame.dwPhase = 0;
    g_DementorMinigame.dwHarryDirection = 1;
    g_DementorMinigame.dwLastDementor = -1;
    g_DementorMinigame.bMisses = 0;

    g_DementorMinigame.pSpellActor = SpawnActor(0, 0x78, 0x78,
                                                (const ObjPalette *)gDementorMinigameSpellPalette);
    g_DementorMinigame.pSpellActor->dwFlags &= ~ActorFlagVisible;
    g_DementorMinigame.pDamageActor = SpawnActor(0, 0x78, 0x78,
                                                 (const ObjPalette *)gDementorMinigameDamagePalette);
    g_DementorMinigame.pDamageActor->dwFlags &= ~ActorFlagVisible;

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

    DrawDementorMinigameScore();
    DrawDementorMinigameLives();
    DrawDementorMinigameMisses();
    SpawnDementorMinigameActors();
    PlayScreenTransitionInByIndex(0x3F, 2);
    PlayMusicModule(0x1E);
}
