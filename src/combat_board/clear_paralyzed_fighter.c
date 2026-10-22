#include "types.h"
#include "combat_board.h"
#include "color.h"
#include "combat_fighter.h"
#include "particles.h"
#include "combat.h"

// Ends a fighter's paralysis: on a successful escape roll, CureAilments, a
// paralysis-curing potion, or fainting. Clears Paralyzed, sets ParalysisImmune,
// and resets the escape-chance ratchet back to its starting value.
void ClearParalyzedFighter_candidate(u8 fighterIndex)
{
    if (g_pFightState->pFighters[fighterIndex].bStatusFlags & Paralyzed)
    {
        Actor *actor;

        g_pFightState->pFighters[fighterIndex].bStatusFlags &= ~Paralyzed;
        g_pFightState->pFighters[fighterIndex].bStatusFlags |= ParalysisImmune;
        g_pFightState->pFighters[fighterIndex].bParalysisEscapeChance = 100;
        g_pFightState->pFighters[fighterIndex].pActor->wActionVariant = 0;

        if (g_pFightState->pFighters[fighterIndex].bFighterType != Enemy)
        {
            if (g_pFightState->pFighters[fighterIndex].pActor->pWindupParticleEmitter != NULL)
            {
                ReleaseParticleEmitter(g_pFightState->pFighters[fighterIndex].pActor->pWindupParticleEmitter);
                g_pFightState->pFighters[fighterIndex].pActor->pWindupParticleEmitter = NULL;
            }

            actor = g_pFightState->pFighters[fighterIndex].pActor;
            SetPlayerActorAnim(actor, 0);

            actor = g_pFightState->pFighters[fighterIndex].pActor;
            {
                u8 fighterType = *(u8 *)&actor->wActorType;
                u8 paletteBank = actor->oam.paletteNum;
                QueueObjPaletteLoad(&g_aFighterAnimTable[fighterType].aRecords[0].pPalette->aColors[1],
                    (paletteBank << 4) + 1, 0xf);
            }
        }
        else
        {
            SetMonsterActorAnim(g_pFightState->pFighters[fighterIndex].pActor, 0);
        }
    }
}
