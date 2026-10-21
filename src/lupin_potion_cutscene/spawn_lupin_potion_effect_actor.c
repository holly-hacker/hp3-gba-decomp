#include "lupin_potion_cutscene.h"
#include "palette.h"

Actor *SpawnLupinPotionEffectActor(s32 kind, FixedPoint pos)
{
    Actor *pActor = AllocActorOfType(6);

    if (pActor != NULL)
    {
        pActor->wCharacterId_candidate = kind;
        pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation;
        pActor->oam.objMode = 0;
        pActor->oam.bpp8 = 0;
        SetActorPendingPalette(pActor, g_aLupinPotionEffectAssets[kind].pPalette);
        SetActorAnimData(pActor, &g_aLupinPotionEffectAssets[kind], g_aLupinPotionEffectAnims[kind], 0);
        SnapActorPosition(pActor, pos.x, pos.y);
        pActor->pfnTick = TickLupinPotionEffectActor;
        pActor->oam.priority = 0;
        pActor->bDepthSortBias = 0x80;
    }
    return pActor;
}
