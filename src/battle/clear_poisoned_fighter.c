#include "types.h"
#include "battle.h"
#include "display.h"

// CurePoison's shared helper -- clears Poisoned, zeroes the per-turn tick
// damage, and refreshes the sprite (undoes the poison discoloration/anim).
// Player-only: called even for an enemy fighter, but only ever does
// anything for a live Poisoned status, and every source of Poisoned so far
// is player-facing (see docs/memory-map/battle.md).
void ClearPoisonedFighter_candidate(u8 fighterIndex)
{
    BattleFighter *fighter = &g_pFightState->pFighters[fighterIndex];
    Object *object = fighter->pObject;

    if (fighter->bStatusFlags & Poisoned)
    {
        fighter->bStatusFlags &= ~Poisoned;
        fighter->bPoisonDamage = 0;
        object->wActionVariant = 0;

        SetPlayerObjectAnim(object, 0);

        if (object->pWindupParticleEmitter != NULL)
        {
            ReleaseParticleEmitter_candidate(object->pWindupParticleEmitter);
            object->pWindupParticleEmitter = NULL;
        }

        {
            u8 paletteBank = object->oam.paletteNum;
            u8 fighterType = *(u8 *)&object->wObjectType;
            sub_0800D264((u8 *)g_aFighterAnimTable[fighterType].nEffectSlotLive + 2,
                (paletteBank << 4) + 1, 0xf);
        }
    }
}
