#include "types.h"
#include "actor.h"
#include "background.h"
#include "hero.h"
#include "map.h"
#include "move.h"
#include "particles.h"

// Ends the active field spell: frees its particles, gives the caster back its state (Reparo) or
// sprite (Lumos), and destroys the effect and companion actors.
void EndFieldSpellEffect(Actor *effect)
{
    u32 spell;

    if (g_dwFieldSpellActive == 1)
    {
        g_dwFieldSpellActive = 0;
        FreeAllParticleEmitters();
        FreeAllParticles();
        ReleaseParticleGfx(2, 0);
        ReleaseParticleGfx(2, 1);
        ReleaseParticleGfx(2, 2);
        ReleaseParticleGfx(2, 3);
        ReleaseParticleGfx(2, 4);
        if (effect != NULL)
        {
            spell = effect->wCharacterId_candidate;
            if (spell == FieldSpellReparo)
            {
                if (effect->pLinkedActor_candidate == g_pPlayerActor)
                    SetActorActionState(effect->pLinkedActor_candidate,
                                        effect->pLinkedActor_candidate->bPrevActionState_candidate);
            }
            else if (spell == FieldSpellLumos)
            {
                g_pPlayerActor->dwFlags &= ~ActorFlagVisible;
                SetActorAssetRecord(g_pPlayerActor, &g_LumosEndPlayerGfx);
                SetActorAnimFrame(g_pPlayerActor, g_abLumosPlayerStandFrames[g_pPlayerActor->bFacing]);
                g_pPlayerActor->dwFlags |= ActorFlagVisible;
                if (g_dwRoomBgFlag_candidate == 0)
                    DisableBg(0);
            }
            g_pFieldSpellEffectActor = NULL;
            effect->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        }
        if (g_pFieldSpellCompanionActor != NULL)
        {
            g_pFieldSpellCompanionActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            g_pFieldSpellCompanionActor = NULL;
        }
    }
}
