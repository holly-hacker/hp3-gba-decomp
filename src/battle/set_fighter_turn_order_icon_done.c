#include "types.h"
#include "battle/battle.h"

// Resets the fighter's turn-order icon portrait to its idle frame; enemy
// fighters use frame 1, party fighters frame 0.
void SetFighterTurnOrderIconDone(s32 fighterIndex)
{
    u8 index = fighterIndex;

    if (g_pFightState->pFighters[index].bFighterType == Enemy)
        SetObjectAnimFrame(g_pFightState->apTurnOrderIconObjects[index]->pLinkedObject_candidate, 1);
    else
        SetObjectAnimFrame(g_pFightState->apTurnOrderIconObjects[index]->pLinkedObject_candidate, 0);
}
