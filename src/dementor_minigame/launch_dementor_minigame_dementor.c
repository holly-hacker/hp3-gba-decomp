#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"

void LaunchDementorMinigameDementor(s32 direction)
{
    SetActorAnimData(g_DementorMinigame.apDementors[direction], &g_DementorMinigameDementorSprite,
                     g_aabDementorFlyAnimData[direction], 0);
    StartDementorMinigameDementorApproach(direction);
}
