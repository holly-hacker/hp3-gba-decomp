#include "types.h"
#include "actor.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_fighter.h"
#include "combat_fx.h"
#include "mem.h"

#define STAGING(i) (g_pFightState->pStagingFighters[i])
#define SLOT(i) (g_pFightState->pFighters[i])
#define FAINTED(i) (g_pFightState->pFaintedAllies[i])

// Brings fainted ally faintedIndex back at full HP and MP and merges it into the turn
// order (ascending bAgility) ahead of the first fighter that is not faster. The active
// and caster indices move past it when it lands at or before the active fighter; its
// bAgility is then set to 0xFF to mark it placed.
void ReviveFighter(u8 faintedIndex)
{
    BattleFighter *pRevived = &FAINTED(faintedIndex);
    u32 i;
    u32 j;

    pRevived->stats.wHp = pRevived->wHp_max;
    g_aPartyMasterStats[pRevived->bFighterType].stats.wHp = pRevived->stats.wHp;
    pRevived->stats.wMp = pRevived->wMp_max;
    g_aPartyMasterStats[pRevived->bFighterType].stats.wMp = pRevived->stats.wMp;
    pRevived->nFaintedFlag = 0xFF;
    SetActorActionState(pRevived->pActor, 0);

    for (i = 0; i < g_pFightState->bFighterCount; i++)
        STAGING(i) = SLOT(i);

    for (i = 0, j = 0; i < g_pFightState->bFighterCount; i++, j++)
    {
        if (STAGING(i).bAgility >= pRevived->bAgility)
        {
            if (STAGING(g_pFightState->bActiveFighterIndex).bAgility
                >= FAINTED(faintedIndex).bAgility)
            {
                g_pFightState->bActiveFighterIndex++;
                g_effectStaging.bCasterIndex++;
            }

            SLOT(j++) = *pRevived;
            SLOT(j) = STAGING(i);
            FAINTED(faintedIndex).bAgility = 0xFF;
        }
        else
        {
            SLOT(j) = STAGING(i);
        }
    }

    if (pRevived->bAgility < 0xFF)
        SLOT(j) = *pRevived;

    g_pFightState->bFaintedAllyCount--;
    if (g_pFightState->bFaintedAllyCount != 0 && faintedIndex == 0)
        FAINTED(0) = FAINTED(1);

    PruneFaintedAndRebuildTurnOrder(1);
}
