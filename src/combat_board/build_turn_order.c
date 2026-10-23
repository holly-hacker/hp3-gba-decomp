#include "types.h"
#include "combat_board.h"
#include "combat_fighter.h"
#include "combat.h"

#define STAGING(i) (g_pFightState->pStagingFighters[i])
#define SLOT(i) (g_pFightState->pFighters[i])

// Selection-sorts pStagingFighters into pFighters ascending by bAgility
// (lower = earlier turn), then spawns each fighter's turn-order icon and
// populates aEnemySlotTurnOrderIndex[bSlotParam]/aAllySlotTurnOrderIndex[bSlotParam].
// Duplicate bAgility values are broken by nudging the loser's stored
// agility up by 1 the first time it ties an already-found winner, keeping the
// sort stable/deterministic.
void BuildTurnOrder(void)
{
    u8 outerIdx;
    u8 winnerIdx;
    u8 prevWinnerAgility;
    u8 bestAgility;
    u8 innerIdx;

    winnerIdx = 0;
    prevWinnerAgility = 0;
    outerIdx = 0;

    // Selection sort, bFighterCount-1 passes; the last fighter is handled
    // by the leftover pass below.
    while (outerIdx < g_pFightState->bFighterCount - 1) {
        bestAgility = 0xff;
        innerIdx = 0;

        while (innerIdx < g_pFightState->bFighterCount) {
            if (STAGING(innerIdx).stats.wHp == 0) {
                STAGING(innerIdx).nTurnKey = -1;
            } else if (STAGING(innerIdx).bAgility < bestAgility && STAGING(innerIdx).bAgility > prevWinnerAgility) {
                bestAgility = STAGING(innerIdx).bAgility;
                winnerIdx = innerIdx;
            } else if (STAGING(innerIdx).bAgility == bestAgility && (u16)STAGING(innerIdx).nTurnKey == 0) {
                // Tie with the current best: bump this fighter's agility by 1
                // so it sorts after its twin instead of being picked again.
                STAGING(innerIdx).bAgility = STAGING(innerIdx).bAgility + 1;
            }

            innerIdx = innerIdx + 1;
        }

        // place the lowest agility at the start
        SLOT(outerIdx) = STAGING(winnerIdx);

        // Mark both copies placed with the slot's turn key.
        SLOT(outerIdx).nTurnKey = g_pFightState->bTurnKeyStep * (outerIdx + 2);

        prevWinnerAgility = STAGING(winnerIdx).bAgility;
        STAGING(winnerIdx).nTurnKey = SLOT(outerIdx).nTurnKey;

        outerIdx = outerIdx + 1;
    }

    // Leftover pass: the one fighter never picked above (nTurnKey
    // still 0) goes into the last pFighters slot, unless it's fainted.
    innerIdx = 0;
    while (innerIdx < g_pFightState->bFighterCount) {
        if ((u16)STAGING(innerIdx).nTurnKey == 0
            && STAGING(innerIdx).stats.wHp != 0) {
            SLOT(outerIdx) = STAGING(innerIdx);
            SLOT(outerIdx).nTurnKey = g_pFightState->bTurnKeyStep * (outerIdx + 2);
        } else if (STAGING(innerIdx).stats.wHp == 0) {
            STAGING(innerIdx).nTurnKey = -1;
        }

        innerIdx = innerIdx + 1;
    }

    // pFighters is now sorted; spawn each fighter's turn-order icon and
    // record its position for target-redirect lookups.
    innerIdx = 0;
    while (innerIdx < g_pFightState->bFighterCount) {
        SLOT(innerIdx).pActor->bFighterIndex = innerIdx;

        if (SLOT(innerIdx).bFighterType != Enemy) {
            SpawnTurnOrderIcon(SLOT(innerIdx).bFighterType, 1, innerIdx,
                               SLOT(innerIdx).pActor->oam.paletteNum);
            g_pFightState->aAllySlotTurnOrderIndex[SLOT(innerIdx).bSlotParam] = innerIdx;
        } else {
            SpawnTurnOrderIcon(SLOT(innerIdx).bRosterIndex, 0, innerIdx,
                               SLOT(innerIdx).pActor->oam.paletteNum);
            g_pFightState->aEnemySlotTurnOrderIndex[SLOT(innerIdx).bSlotParam] = innerIdx;
        }

        innerIdx = innerIdx + 1;
    }
}
