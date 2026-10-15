#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"

// Retreats at twice the approach speed, and never slower than after six repelled.
void StartDementorMinigameDementorRetreat(s32 direction)
{
    s32 repelled;

    repelled = g_DementorMinigame.dwRepelled;
    if (repelled < 6)
        g_DementorMinigame.dwRepelled = 6;

    switch (direction)
    {
    case 0:
        SetActorVelocity(g_DementorMinigame.apDementors[0], GetDementorMinigameDementorVelocity(1, 2), 0);
        break;
    case 1:
        SetActorVelocity(g_DementorMinigame.apDementors[1], 0, GetDementorMinigameDementorVelocity(1, 2));
        break;
    case 2:
        SetActorVelocity(g_DementorMinigame.apDementors[2], GetDementorMinigameDementorVelocity(0, 2), 0);
        break;
    case 3:
        SetActorVelocity(g_DementorMinigame.apDementors[3], 0, GetDementorMinigameDementorVelocity(0, 2));
        break;
    }

    g_DementorMinigame.dwRepelled = repelled;
}
