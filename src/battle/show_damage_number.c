#include "types.h"
#include "battle/battle.h"

// Shows `damage` over fighter `targetIndex` and puts its Object into action
// state 2. An out-of-range target is retargeted to the first living fighter
// on the opposite side from the active fighter (none: nothing is shown), and
// the active fighter's bSelectedActionIndex is updated to it.
void ShowDamageNumber_candidate(s32 targetIndex, s32 damage)
{
    u8 target = targetIndex;
    u16 amount = damage;
    u32 i;

    if (target >= g_pFightState->bFighterCount) {
        target = 0xFF;

        for (i = 0; target == 0xFF && i < g_pFightState->bFighterCount; i++) {
            if (ACTIVE_FIGHTER.bFighterType == Enemy) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy && g_pFightState->pFighters[i].wHp != 0)
                    target = i;
            } else {
                if (g_pFightState->pFighters[i].bFighterType == Enemy && g_pFightState->pFighters[i].wHp != 0)
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

    g_pFightState->pFighters[target].pObject->modeState.actor.wStagedDamage = amount;
    SetObjectActionState(g_pFightState->pFighters[target].pObject, 2);
}
