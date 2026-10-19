#include "types.h"
#include "combat_board.h"
#include "combat_fighter.h"
#include "combat.h"

// Heals an ally fighter by amount, capped at max HP, in both the battle and
// master records. Returns the HP actually restored.
s32 RestoreFighterHp(s32 amount, s32 fighterIndex)
{
    u16 hp;
    u16 maxHp;
    BattleFighter *master;
    FightState *fs;
    BattleFighter *party;

    party = g_aPartyMasterStats;
    fs = g_pFightState;
    master = &party[fs->pFighters[fighterIndex].bFighterType];
    hp = master->stats.wHp;
    maxHp = master->wHp_max;
    hp += amount;
    if (hp > maxHp)
    {
        amount -= hp - maxHp;
        hp = maxHp;
    }
    master->stats.wHp = hp;
    fs->pFighters[fighterIndex].stats.wHp = hp;
    if (fs->bActiveFighterIndex == fighterIndex)
        DrawFighterStatsUi(fs->pFighters[fighterIndex].bFighterType, 0);

    return amount;
}
