#include "types.h"
#include "actor.h"
#include "palette.h"
#include "particles.h"
#include "spongify_pad_actor.h"
#include "gen/graphics/overworld.h"

// Spawns the effect that trails the player launched from pPad; see TickSpongifyPadEffect.
void SpawnSpongifyPadEffect(Actor *pPad, Actor *pPlayer)
{
    Actor *pEffect = AllocActorOfType(RoomActorType_SpongifyPadEffect);

    pEffect->oam.priority = 1;
    pEffect->bDepthSortBias = 0;
    pEffect->pos = pPlayer->pos;
    pEffect->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation | ActorFlagUnk2000;
    pEffect->nMoveSpeed = 1;
    pEffect->pfnTick = TickSpongifyPadEffect;
    SetActorPendingPalette(pEffect, gSpongifyEffectPalette);
    SetActorAnimData(pEffect, &g_aRoomSpongifyPadSprites[3], &g_abRoomSpongifyPadAnimData[10], 0);
    SetActorActionSubState(pEffect, 0);
    LoadParticleGfx(2, 2, (const ActorAssetRecord *)&g_RoomSpongifyPadParticleGfx0);
    LoadParticleGfx(2, 3, (const ActorAssetRecord *)&g_RoomSpongifyPadParticleGfx1);
    pEffect->pfnTick = TickSpongifyPadEffect;
    pEffect->pOwnerActor = pPlayer;
}
