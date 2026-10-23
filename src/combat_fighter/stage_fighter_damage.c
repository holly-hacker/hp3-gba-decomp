#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Stages `damage` on fighter `targetIndex` (wStagedDamage) and puts its Actor into
// action state 2, the hurt state; a party member takes the damage when its hurt
// animation ends. An out-of-range target is retargeted to the first living fighter
// on the opposite side from the active fighter (none: nothing happens), and the
// active fighter's bSelectedActionIndex is updated to it.
void StageFighterDamage(s32 targetIndex, s32 damage)
{
    u8 target = targetIndex;
    u16 amount = damage;
    u32 i;

    if (target >= g_pFightState->bFighterCount) {
        target = 0xFF;

        for (i = 0; target == 0xFF && i < g_pFightState->bFighterCount; i++) {
            if (ACTIVE_FIGHTER.bFighterType == Enemy) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy && g_pFightState->pFighters[i].stats.wHp != 0)
                    target = i;
            } else {
                if (g_pFightState->pFighters[i].bFighterType == Enemy && g_pFightState->pFighters[i].stats.wHp != 0)
                    target = i;
            }
        }

        if (target == 0xFF)
            return;

        if (ACTIVE_FIGHTER.bFighterType == Enemy)
            ACTIVE_FIGHTER.bSelectedActionIndex = target;
        else
            ACTIVE_FIGHTER.bSelectedActionIndex = target;
    }

    g_pFightState->pFighters[target].pActor->modeState.actor.wStagedDamage = amount;
    SetActorActionState(g_pFightState->pFighters[target].pActor, 2);
}
