#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/graphics.h"

// Shared cleanup for a fighter escaping Paralyzed, both on a successful
// escape roll (RollFighterParalysisEscape) and from CureAilments. Clears
// Paralyzed, sets the paired unnamed 0x80 status bit, and resets the
// escape-chance ratchet back to its starting value.
void ClearParalyzedFighter_candidate(u8 fighterIndex)
{
    if (g_pFightState->pFighters[fighterIndex].bStatusFlags & Paralyzed)
    {
        Actor *actor;

        g_pFightState->pFighters[fighterIndex].bStatusFlags &= ~Paralyzed;
        g_pFightState->pFighters[fighterIndex].bStatusFlags |= 0x80;
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
