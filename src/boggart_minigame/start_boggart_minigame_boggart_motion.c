#include "actor.h"
#include "boggart_minigame.h"

void StartBoggartMinigameBoggartMotion(void)
{
    SetActorAnimData(g_BoggartMinigame.pActor, &g_aBoggartFormAssets[g_BoggartMinigame.dwBoggartDirection],
                     g_aabBoggartWalkAnimData[g_BoggartMinigame.dwBoggartDirection], 0);

    switch (g_BoggartMinigame.dwBoggartDirection)
    {
    case 0:
        SetActorVelocity(g_BoggartMinigame.pActor, GetBoggartMinigameBoggartVelocity(1), 0);
        break;
    case 1:
        SetActorVelocity(g_BoggartMinigame.pActor, 0, GetBoggartMinigameBoggartVelocity(1));
        break;
    case 2:
        SetActorVelocity(g_BoggartMinigame.pActor, GetBoggartMinigameBoggartVelocity(0), 0);
        break;
    case 3:
        SetActorVelocity(g_BoggartMinigame.pActor, 0, GetBoggartMinigameBoggartVelocity(0));
        break;
    }
}
