#include "actor.h"
#include "dementor_minigame.h"

void ShowDementorMinigameDamage(void)
{
    SetActorAnimData(g_DementorMinigame.pDamageActor, &g_DementorMinigameDamageSprite,
                     g_abDementorMinigameDamageAnimData, 0);
    g_DementorMinigame.pDamageActor->dwFlags |= ActorFlagVisible;
    g_DementorMinigame.dwDamageHideTimer = 17;
}
