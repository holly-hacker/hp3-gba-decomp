#include "types.h"
#include "actor.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "boggart_minigame.h"

void StartBoggartMinigameCast(u32 direction)
{
    g_BoggartMinigame.dwChosenDirection = direction;
    SetActorAnimData(g_BoggartMinigame.apStudents[direction], &g_aBoggartStudentAssets[direction],
                     g_abBoggartStudentCastAnimData, 0);

    if (direction == g_BoggartMinigame.dwBoggartDirection)
        PlaySoundById(0x50);
    else
        PlaySoundById(0x4B);

    g_BoggartMinigame.dwCountdown = 6;
    g_GameModeStackContext.dwModeState = BoggartMinigameStateResolve;
}
