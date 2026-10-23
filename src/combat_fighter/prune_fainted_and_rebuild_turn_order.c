#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Removes every fighter marked fainted (nTurnKey == -1) from pFighters,
// moving fainted party members to pFaintedAllies, then tears down
// and respawns all turn-order icons, renumbers the fighters' turn keys and
// records the key of the fighter after the active one.
// addRevivedAlly makes room for the ally ReviveFighter just merged in (bFighterCount + 1).
void PruneFaintedAndRebuildTurnOrder(s32 addRevivedAlly)
{
    u8 i;
    u8 j;
    u8 k;
    u8 count;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        g_pFightState->apTurnOrderIconActors[i]->pLinkedActor->dwFlags
            |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        g_pFightState->apTurnOrderIconActors[i]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        g_pFightState->apTurnOrderIconActors[i] = 0;
    }

    for (i = 0; i < 3; i++) {
        g_pFightState->aAllySlotTurnOrderIndex[i] |= 0xFF;
        g_pFightState->aEnemySlotTurnOrderIndex[i] |= 0xFF;
    }

    if (addRevivedAlly)
        g_pFightState->bFighterCount++;

    count = g_pFightState->bFighterCount;

    for (i = 0, j = 0; i < count; i++, j++) {
        if ((u16)g_pFightState->pFighters[j].nTurnKey == 0xFFFF) {
            g_pFightState->bFighterCount--;

            if (g_pFightState->pFighters[j].bFighterType != Enemy) {
                g_pFightState->pFaintedAllies[g_pFightState->bFaintedAllyCount] = g_pFightState->pFighters[j];
                g_pFightState->bFaintedAllyCount++;
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
        g_pFightState->pFighters[i].nTurnKey = g_pFightState->bTurnKeyStep * (i + 2);
        g_pFightState->pFighters[i].pActor->bFighterIndex = i;

        if (g_pFightState->pFighters[i].bFighterType != Enemy) {
            SpawnTurnOrderIcon(g_pFightState->pFighters[i].bFighterType, 1, i,
                               g_pFightState->pFighters[i].pActor->oam.paletteNum);
            g_pFightState->aAllySlotTurnOrderIndex[g_pFightState->pFighters[i].bSlotParam] = i;
        } else {
            SpawnTurnOrderIcon(g_pFightState->pFighters[i].bRosterIndex, 0, i,
                               g_pFightState->pFighters[i].pActor->oam.paletteNum);
            g_pFightState->aEnemySlotTurnOrderIndex[g_pFightState->pFighters[i].bSlotParam] = i;
        }
    }

    if (g_pFightState->bActiveFighterIndex + 1 == g_pFightState->bFighterCount)
        g_pFightState->wNextFighterTurnKey = g_pFightState->pFighters[0].nTurnKey;
    else
        g_pFightState->wNextFighterTurnKey = g_pFightState->pFighters[g_pFightState->bActiveFighterIndex + 1].nTurnKey;
}
