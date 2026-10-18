#include "types.h"
#include "combat_board.h"
#include "color.h"
#include "combat_fighter.h"
#include "particles.h"
#include "combat.h"

// CurePoison's shared helper -- clears Poisoned, zeroes the per-turn tick
// damage, and refreshes the sprite (undoes the poison discoloration/anim).
// Player-only: called even for an enemy fighter, but only ever does
// anything for a live Poisoned status, and every source of Poisoned so far
// is player-facing (see docs/memory-map/battle.md).
void ClearPoisonedFighter_candidate(u8 fighterIndex)
{
    BattleFighter *fighter = &g_pFightState->pFighters[fighterIndex];
    Actor *actor = fighter->pActor;

    if (fighter->bStatusFlags & Poisoned)
    {
        fighter->bStatusFlags &= ~Poisoned;
        fighter->bPoisonDamage = 0;
        actor->wActionVariant = 0;

        SetPlayerActorAnim(actor, 0);

        if (actor->pWindupParticleEmitter != NULL)
        {
            ReleaseParticleEmitter(actor->pWindupParticleEmitter);
            actor->pWindupParticleEmitter = NULL;
        }

        {
            u8 paletteBank = actor->oam.paletteNum;
            u8 fighterType = *(u8 *)&actor->wActorType;
            QueueObjPaletteLoad(&g_aFighterAnimTable[fighterType].aRecords[0].pPalette->aColors[1],
                (paletteBank << 4) + 1, 0xf);
        }
    }
}
