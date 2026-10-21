#include "lupin_potion_cutscene.h"

void SpawnLupinPotionCast(void)
{
    s32 i;

    for (i = 0; i < LUPIN_POTION_CAST_COUNT; i++)
    {
        g_LupinPotionCutscene.apCast[i] = SpawnLupinPotionCastActor(i);
        SetActorVelocity(g_LupinPotionCutscene.apCast[i], -0x20000, 0);
    }
}
