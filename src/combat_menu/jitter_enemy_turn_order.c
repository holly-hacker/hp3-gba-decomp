#include "types.h"
#include "battle/battle.h"
#include "combat_menu.h"
#include "random.h"
#include "combat.h"

// Adds +/-16 random jitter to each Enemy fighter's bAgility (clamped
// [5,251]) before BuildTurnOrder sorts by it. Runs on pStagingFighters,
// ahead of the roster compaction/copy into pFighters.
void JitterEnemyTurnOrder(void)
{
    u32 i;
    s32 agility;

    i = 0;
    if (i < g_pFightState->bFighterCount) {
        do {
            // NOTE: RNG is still advanced for party fighters, but result is discarded
            agility = g_pFightState->pStagingFighters[i].bAgility + Mt19937RandSigned(0x10);

            if (agility > 250)
                agility = 251;
            else if (agility < 5)
                agility = 5;

            if (g_pFightState->pStagingFighters[i].bFighterType == Enemy)
                g_pFightState->pStagingFighters[i].bAgility = agility;

            i++;
        } while (i < g_pFightState->bFighterCount);
    }
}
