#include "types.h"
#include "battle/battle.h"

// Highlights the fighter's turn-order icon portrait (frame 3 for enemies, 2
// for party members) and gives it the front draw-order bias; every other
// fighter's icon is pushed behind it.
void SetFighterTurnOrderIconActive(s32 fighterIndex)
{
    u8 index = fighterIndex;
    u8 i;

    if (g_pFightState->pFighters[index].bFighterType == Enemy)
        SetObjectAnimFrame(g_pFightState->apTurnOrderIconObjects[index]->pLinkedObject_candidate, 3);
    else
        SetObjectAnimFrame(g_pFightState->apTurnOrderIconObjects[index]->pLinkedObject_candidate, 2);

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (i == index) {
            g_pFightState->apTurnOrderIconObjects[i]->pLinkedObject_candidate->bDepthSortBias = 0xFD;
            g_pFightState->apTurnOrderIconObjects[i]->bDepthSortBias = 0x80;
        } else {
            g_pFightState->apTurnOrderIconObjects[i]->pLinkedObject_candidate->bDepthSortBias = 0xFF;
            g_pFightState->apTurnOrderIconObjects[i]->bDepthSortBias = 0xFE;
        }
    }
}
