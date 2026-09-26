#include "types.h"
#include "battle.h"
#include "display.h"

// Shared cleanup for a fighter escaping Paralyzed, both on a successful
// escape roll (RollFighterParalysisEscape) and from CureAilments. Clears
// Paralyzed, sets the paired unnamed 0x80 status bit, and resets the
// escape-chance ratchet back to its starting value.
void ClearParalyzedFighter_candidate(u8 fighterIndex)
{
    if (g_pFightState->pFighters[fighterIndex].bStatusFlags & Paralyzed)
    {
        Object *object;

        g_pFightState->pFighters[fighterIndex].bStatusFlags &= ~Paralyzed;
        g_pFightState->pFighters[fighterIndex].bStatusFlags |= 0x80;
        g_pFightState->pFighters[fighterIndex].bParalysisEscapeChance = 100;
        g_pFightState->pFighters[fighterIndex].pObject->wActionVariant = 0;

        if (g_pFightState->pFighters[fighterIndex].bFighterType != Enemy)
        {
            if (g_pFightState->pFighters[fighterIndex].pObject->pWindupParticleEmitter != NULL)
            {
                ReleaseParticleEmitter_candidate(g_pFightState->pFighters[fighterIndex].pObject->pWindupParticleEmitter);
                g_pFightState->pFighters[fighterIndex].pObject->pWindupParticleEmitter = NULL;
            }

            object = g_pFightState->pFighters[fighterIndex].pObject;
            SetPlayerObjectAnim(object, 0);

            object = g_pFightState->pFighters[fighterIndex].pObject;
            {
                u8 fighterType = *(u8 *)&object->wObjectType;
                u8 paletteBank = object->oam.paletteNum;
                sub_0800D264((u8 *)g_aFighterAnimTable[fighterType].pPaletteLive + 2,
                    (paletteBank << 4) + 1, 0xf);
            }
        }
        else
        {
            SetMonsterObjectAnim(g_pFightState->pFighters[fighterIndex].pObject, 0);
        }
    }
}
