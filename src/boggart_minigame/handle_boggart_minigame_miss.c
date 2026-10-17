#include "types.h"
#include "actor.h"
#include "sound.h"
#include "graphics/display.h"
#include "modes.h"
#include "boggart_minigame_inline.h"

void HandleBoggartMinigameMiss(u32 playSound)
{
    u32 soundId;

    SetActorVelocity(g_BoggartMinigame.pActor, 0, 0);
    SetActorAnimFrame(g_BoggartMinigame.pActor, 0);
    SetActorAnimFrame(g_BoggartMinigame.apStudents[g_BoggartMinigame.dwBoggartDirection], 7);

    if (playSound)
    {
        switch (g_BoggartMinigame.dwBoggartDirection)
        {
        case 0:
            soundId = 0xA2;
            break;
        case 1:
            soundId = 0xA0;
            break;
        case 2:
            soundId = 0x9F;
            break;
        case 3:
            soundId = 0xA6;
            break;
        default:
            soundId = 0;
            break;
        }
        PlaySoundById(soundId);
    }

    ClearBoggartMinigameMessage();
    DrawBoggartMinigameMessage(0x58D);  // "Failed!"

    g_BoggartMinigame.bLives--;

    DrawBoggartMinigameLives();

    g_BoggartMinigame.dwCountdown = 25;
    g_GameModeStackContext.dwModeState = BoggartMinigameStateRoundEnd;
}
