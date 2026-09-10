#include "types.h"
#include "battle.h"
#include "mt19937.h"

// Adds +/-16 random jitter to each Enemy fighter's bStat_speed (clamped
// [5,251]) before BuildTurnOrder sorts by it. Runs on pStagingFighters,
// ahead of the roster compaction/copy into pFighters.
void JitterEnemyTurnOrder(void)
{
    u32 i;
    s32 speed;

    i = 0;
    if (i < g_pFightState->bFighterCount) {
        do {
            speed = g_pFightState->pStagingFighters[i].bStat_speed + Mt19937RandSigned(0x10);

            if (speed > 250)
                speed = 251;
            else if (speed < 5)
                speed = 5;

            if (g_pFightState->pStagingFighters[i].bFighterType == Enemy)
                g_pFightState->pStagingFighters[i].bStat_speed = speed;

            i++;
        } while (i < g_pFightState->bFighterCount);
    }
}
