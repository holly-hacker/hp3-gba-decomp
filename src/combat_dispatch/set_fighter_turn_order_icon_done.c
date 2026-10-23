#include "types.h"
#include "combat_dispatch.h"
#include "combat.h"

// Resets the fighter's turn-order icon portrait to its idle frame; enemy
// fighters use frame 1, party fighters frame 0.
void SetFighterTurnOrderIconDone(s32 fighterIndex)
{
    u8 index = fighterIndex;

    if (g_pFightState->pFighters[index].bFighterType == Enemy)
        SetActorAnimFrame(g_pFightState->apTurnOrderIconActors[index]->pLinkedActor, 1);
    else
        SetActorAnimFrame(g_pFightState->apTurnOrderIconActors[index]->pLinkedActor, 0);
}
