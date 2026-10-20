#include "actor.h"
#include "hero.h"
#include "overworld/overworld.h"

Actor *SpawnFieldSpellIconActor(void)
{
    Actor *pActor;

    pActor = AllocActorOfType(0xE);
    SnapActorPosition(pActor, 0, 0);
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
                    | ActorFlagHasSpriteCells;
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = NULL;
    pActor->oam.objMode = 0;
    pActor->oam.bpp8 = 0;
    pActor->oam.priority = 0;
    pActor->bDepthSortBias = 0x80;
    pActor->oam.paletteNum = 2;
    RefreshFieldSpellHud(pActor);
    g_pFieldSpellIconActor = pActor;
    return pActor;
}
