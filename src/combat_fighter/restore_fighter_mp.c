#include "types.h"
#include "combat_board.h"
#include "combat_fighter.h"
#include "combat.h"

// Restores an ally fighter's MP by amount, capped at max MP, in both the battle and
// master records. Returns the MP actually restored.
s32 RestoreFighterMp(s32 amount, s32 fighterIndex)
{
    u16 mp;
    u16 maxMp;
    BattleFighter *master;
    FightState *fs;
    BattleFighter *party;

    party = g_aPartyMasterStats;
    fs = g_pFightState;
    master = &party[fs->pFighters[fighterIndex].bFighterType];
    mp = master->stats.wMp;
    maxMp = master->wMp_max;
    mp += amount;
    if (mp > maxMp)
    {
        amount -= mp - maxMp;
        mp = maxMp;
    }
    master->stats.wMp = mp;
    fs->pFighters[fighterIndex].stats.wMp = mp;
    if (fs->bMenuFighterIndex == fighterIndex)
        DrawFighterStatsUi(fs->pFighters[fighterIndex].bFighterType, 0);

    return amount;
}
