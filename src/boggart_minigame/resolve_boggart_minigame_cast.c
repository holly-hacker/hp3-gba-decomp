#include "types.h"
#include "actor.h"
#include "boggart_minigame.h"

void ResolveBoggartMinigameCast(void)
{
    Actor *pStudent;

    if (g_BoggartMinigame.dwBoggartDirection == g_BoggartMinigame.dwChosenDirection)
    {
        pStudent = g_BoggartMinigame.apStudents[g_BoggartMinigame.dwBoggartDirection];
        g_BoggartMinigame.pCastEffectActor =
            SpawnActor(10, (s16)(pStudent->pos.x >> 16), (s16)(pStudent->pos.y >> 16),
                       g_apBoggartCastEffectPalettes[g_BoggartMinigame.dwBoggartDirection]);
        SetActorAnimData(g_BoggartMinigame.pCastEffectActor,
                         &g_aBoggartCastEffectAssets[g_BoggartMinigame.dwChosenDirection],
                         g_abBoggartCastEffectAnimData, 0);
        g_BoggartMinigame.pCastEffectActor->oam.priority = 2;
        HandleBoggartMinigameHit();
    }
    else
    {
        g_BoggartMinigame.pCastEffectActor = NULL;
        HandleBoggartMinigameMiss(0);
    }
}
