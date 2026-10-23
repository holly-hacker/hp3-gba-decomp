#include "types.h"
#include "combat.h"
#include "combat_gauge.h"

void DestroySlotSpGauge(u32 slot, u32 isAlly)
{
    u8 *slotOrder;
    u8 fighterIndex;

    if (!isAlly)
        slotOrder = g_pFightState->aEnemySlotTurnOrderIndex;
    else
        slotOrder = g_pFightState->aAllySlotTurnOrderIndex;
    fighterIndex = slotOrder[slot];
    DestroyLinkedActor(g_pFightState->pFighters[fighterIndex].pActor->pLinkedActor);
}
