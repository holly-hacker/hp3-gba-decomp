#include "types.h"
#include "battle/battle.h"

// Removes every fighter marked fainted (nFaintedFlag == -1) from pFighters,
// queueing non-Enemy ones onto pPendingFighters_candidate, then tears down
// and respawns all turn-order icons, renumbers the fighters' turn keys and
// records the key of the fighter after the active one.
// addPendingFighter makes room for one more fighter first (bFighterCount + 1).
void PruneFaintedAndRebuildTurnOrder_candidate(s32 addPendingFighter)
{
    u8 i;
    u8 j;
    u8 k;
    u8 count;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        g_pFightState->apTurnOrderIconObjects[i]->pLinkedObject_candidate->dwFlags |= 0x82;
        g_pFightState->apTurnOrderIconObjects[i]->dwFlags |= 0x82;
        g_pFightState->apTurnOrderIconObjects[i] = 0;
    }

    for (i = 0; i < 3; i++) {
        g_pFightState->aAllySlotTurnOrderIndex[i] |= 0xFF;
        g_pFightState->aEnemySlotTurnOrderIndex[i] |= 0xFF;
    }

    if (addPendingFighter)
        g_pFightState->bFighterCount++;

    count = g_pFightState->bFighterCount;

    for (i = 0, j = 0; i < count; i++, j++) {
        if ((u16)g_pFightState->pFighters[j].nFaintedFlag == 0xFFFF) {
            g_pFightState->bFighterCount--;

            if (g_pFightState->pFighters[j].bFighterType != Enemy) {
                g_pFightState->pPendingFighters_candidate[g_pFightState->bPendingFighterCount_candidate] = g_pFightState->pFighters[j];
                g_pFightState->bPendingFighterCount_candidate++;
            }

            for (k = j; k < count - 1; k++) {
                g_pFightState->pFighters[k] = g_pFightState->pFighters[k + 1];

                if (g_pFightState->bActiveFighterIndex == k + 1)
                    g_pFightState->bActiveFighterIndex = k;

                if (g_pFightState->bMenuFighterIndex == k + 1)
                    g_pFightState->bMenuFighterIndex = k;
            }

            j = j - 1;
        }
    }

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        g_pFightState->pFighters[i].nFaintedFlag = g_pFightState->bEnemyScalePercent_candidate * (i + 2);
        g_pFightState->pFighters[i].pObject->bFighterIndex = i;

        if (g_pFightState->pFighters[i].bFighterType != Enemy) {
            SpawnTurnOrderIcon(g_pFightState->pFighters[i].bFighterType, 1, i,
                               g_pFightState->pFighters[i].pObject->oam.paletteNum);
            g_pFightState->aAllySlotTurnOrderIndex[g_pFightState->pFighters[i].bSlotParam] = i;
        } else {
            SpawnTurnOrderIcon(g_pFightState->pFighters[i].bRosterIndex, 0, i,
                               g_pFightState->pFighters[i].pObject->oam.paletteNum);
            g_pFightState->aEnemySlotTurnOrderIndex[g_pFightState->pFighters[i].bSlotParam] = i;
        }
    }

    if (g_pFightState->bActiveFighterIndex + 1 == g_pFightState->bFighterCount)
        g_pFightState->wNextFighterTurnKey_candidate = g_pFightState->pFighters[0].nFaintedFlag;
    else
        g_pFightState->wNextFighterTurnKey_candidate = g_pFightState->pFighters[g_pFightState->bActiveFighterIndex + 1].nFaintedFlag;
}
