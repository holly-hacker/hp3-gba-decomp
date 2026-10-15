#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"

void StartDementorMinigameDementorApproach(s32 direction)
{
    switch (direction)
    {
    case 0:
        SetActorVelocity(g_DementorMinigame.apDementors[0], GetDementorMinigameDementorVelocity(0, 1), 0);
        break;
    case 1:
        SetActorVelocity(g_DementorMinigame.apDementors[1], 0, GetDementorMinigameDementorVelocity(0, 1));
        break;
    case 2:
        SetActorVelocity(g_DementorMinigame.apDementors[2], GetDementorMinigameDementorVelocity(1, 1), 0);
        break;
    case 3:
        SetActorVelocity(g_DementorMinigame.apDementors[3], 0, GetDementorMinigameDementorVelocity(1, 1));
        break;
    }
}
