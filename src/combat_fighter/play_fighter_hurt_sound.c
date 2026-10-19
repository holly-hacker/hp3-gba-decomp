#include "types.h"
#include "combat_fighter.h"
#include "sound.h"
#include "combat.h"

// Plays a party fighter's hurt sound for a hit: the heavy one for a critical
// (1000 or 1001) or a hit of more than a third of max HP.
void PlayFighterHurtSound(u16 damage, u8 fighterType)
{
    u32 heavy;

    if (damage == 0)
        return;

    if ((u16)(damage - 1000) <= 1)
        heavy = 1;
    else if (damage > (u16)(g_aPartyMasterStats[fighterType].wHp_max / 3))
        heavy = 1;
    else
        heavy = 0;

    PlaySoundById(g_aabFighterHurtSoundIds[fighterType][heavy]);
}
