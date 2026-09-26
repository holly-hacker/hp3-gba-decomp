#include "types.h"
#include "battle.h"

#define STAGING(i) (g_pFightState->pStagingFighters[i])
#define SLOT(i) (g_pFightState->pFighters[i])

// Selection-sorts pStagingFighters into pFighters ascending by bSpeed
// (lower = earlier turn), then spawns each fighter's turn-order icon and
// populates aEnemySlotTurnOrderIndex[bSlotParam]/aAllySlotTurnOrderIndex[bSlotParam].
// Duplicate bSpeed values are broken by nudging the loser's stored
// speed up by 1 the first time it ties an already-found winner, keeping the
// sort stable/deterministic. See docs/memory-map/battle.md.
void BuildTurnOrder(void)
{
    u8 outerIdx;
    u8 winnerIdx;
    u8 prevWinnerSpeed;
    u8 bestSpeed;
    u8 innerIdx;

    winnerIdx = 0;
    prevWinnerSpeed = 0;
    outerIdx = 0;

    // Selection sort, bFighterCount-1 passes; the last fighter is handled
    // by the leftover pass below.
    while (outerIdx < g_pFightState->bFighterCount - 1) {
        bestSpeed = 0xff;
        innerIdx = 0;

        while (innerIdx < g_pFightState->bFighterCount) {
            if (STAGING(innerIdx).wHp == 0) {
                STAGING(innerIdx).nFaintedFlag = -1;
            } else if (STAGING(innerIdx).bSpeed < bestSpeed && STAGING(innerIdx).bSpeed > prevWinnerSpeed) {
                bestSpeed = STAGING(innerIdx).bSpeed;
                winnerIdx = innerIdx;
            } else if (STAGING(innerIdx).bSpeed == bestSpeed && (u16)STAGING(innerIdx).nFaintedFlag == 0) {
                // Tie with the current best: bump this fighter's speed by 1
                // so it sorts after its twin instead of being picked again.
                STAGING(innerIdx).bSpeed = STAGING(innerIdx).bSpeed + 1;
            }

            innerIdx = innerIdx + 1;
        }

        // place the lowest speed at the start
        SLOT(outerIdx) = STAGING(winnerIdx);

        // Use nFaintedFlag to mark the enemy as placed
        // TODO: unsure what this multiply does. nFaintedFlag is only used to indicate placement so this multiplication
        // by a static value doesn't accomplish anything.
        SLOT(outerIdx).nFaintedFlag = g_pFightState->bEnemyScalePercent_candidate * (outerIdx + 2);

        prevWinnerSpeed = STAGING(winnerIdx).bSpeed;
        STAGING(winnerIdx).nFaintedFlag = SLOT(outerIdx).nFaintedFlag;

        outerIdx = outerIdx + 1;
    }

    // Leftover pass: the one fighter never picked above (nFaintedFlag
    // still 0) goes into the last pFighters slot, unless it's fainted.
    innerIdx = 0;
    while (innerIdx < g_pFightState->bFighterCount) {
        if ((u16)STAGING(innerIdx).nFaintedFlag == 0
            && STAGING(innerIdx).wHp != 0) {
            SLOT(outerIdx) = STAGING(innerIdx);
            SLOT(outerIdx).nFaintedFlag = g_pFightState->bEnemyScalePercent_candidate * (outerIdx + 2);
        } else if (STAGING(innerIdx).wHp == 0) {
            STAGING(innerIdx).nFaintedFlag = -1;
        }

        innerIdx = innerIdx + 1;
    }

    // pFighters is now sorted; spawn each fighter's turn-order icon and
    // record its position for target-redirect lookups.
    innerIdx = 0;
    while (innerIdx < g_pFightState->bFighterCount) {
        SLOT(innerIdx).pObject->bFighterIndex = innerIdx;

        if (SLOT(innerIdx).bFighterType != Enemy) {
            SpawnTurnOrderIcon(SLOT(innerIdx).bFighterType, 1, innerIdx,
                               SLOT(innerIdx).pObject->bGfxSlot);
            g_pFightState->aAllySlotTurnOrderIndex[SLOT(innerIdx).bSlotParam] = innerIdx;
        } else {
            SpawnTurnOrderIcon(SLOT(innerIdx).bRosterIndex, 0, innerIdx,
                               SLOT(innerIdx).pObject->bGfxSlot);
            g_pFightState->aEnemySlotTurnOrderIndex[SLOT(innerIdx).bSlotParam] = innerIdx;
        }

        innerIdx = innerIdx + 1;
    }
}
