#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "palette.h"
#include "particles.h"
#include "spongify_pad_actor.h"
#include "gen/graphics/overworld.h"

// pfnTick of the effect that trails the launched player: sub-state 0 starts its
// particles, and once the player leaves action state 0x10 sub-state 5 frees them and
// restores the party's flags, draw layer and depth sort bias.
void TickSpongifyPadEffect(Actor *pEffect)
{
    ParticleEmitter *pEmitter;

    if (pEffect->pOwnerActor->bActionState != 0x10)
        pEffect->bActionSubState = 5;

    switch (pEffect->bActionSubState)
    {
    case 0:
        pEffect->bActionSubState = 3;
        pEffect->dwStateTimer = 6;
        pEmitter = AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 2);
        pEmitter->pTarget = pEffect;
        InitSpongifyPadParticleEmitter0(pEmitter, pEffect);
        pEmitter = AllocParticleEmitter((const ObjPalette *)gSpongifyEffectPalette, 2, 3);
        pEmitter->pTarget = pEffect;
        InitSpongifyPadParticleEmitter1(pEmitter, pEffect);
        g_dwFieldSpellActive = 1;
        break;
    case 5:
        g_dwFieldSpellActive = 0;
        pEffect->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        FreeAllParticleEmitters();
        FreeAllParticles();
        ReleaseParticleGfx(2, 2);
        ReleaseParticleGfx(2, 3);
        SetActorFlags(g_pPlayerActor, ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate
                                          | ActorFlagTerrainDrawLayer);
        SetActorDrawLayer(g_pPlayerActor, 1);
        SetActorDepthSortBias(g_pPlayerActor, 0x80);
        if (g_pFollowerActor0 != NULL)
        {
            SetActorFlags(g_pFollowerActor0, ActorFlagTerrainDrawLayer);
            SetActorDrawLayer(g_pFollowerActor0, 1);
            SetActorDepthSortBias(g_pFollowerActor0, 0x80);
        }
        if (g_pFollowerActor1 != NULL)
        {
            SetActorFlags(g_pFollowerActor1, ActorFlagTerrainDrawLayer);
            SetActorDrawLayer(g_pFollowerActor1, 1);
            SetActorDepthSortBias(g_pFollowerActor1, 0x80);
        }
        break;
    case 1:
    case 3:
    case 11:
        break;
    }
}
