#include "types.h"
#include "actor.h"
#include "boggart_minigame.h"

void ResetBoggartMinigameActors(void)
{
    Actor **ppStudent = g_BoggartMinigame.apStudents;
    s32 i;

    for (i = 3; i >= 0; i--)
        SetActorAnimFrame(*ppStudent++, 0);

    if (g_BoggartMinigame.pCastEffectActor != NULL)
        g_BoggartMinigame.pCastEffectActor->dwFlags |= 0x82;
    g_BoggartMinigame.pCastEffectActor = NULL;
}
