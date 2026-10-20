#include "types.h"
#include "combat_fighter.h"
#include "map.h"

u32 PickMaxDamageMonster(const u8 *pSlots)
{
    u32 maxDamage = 0;
    u32 monsterId = 0;
    u32 i;
    u32 damage;

    for (i = 0; i <= 2; i++)
    {
        damage = GetMonsterDamageMax(pSlots[i]);
        if (damage > maxDamage && pSlots[i] != 0xFF)
        {
            maxDamage = damage;
            monsterId = pSlots[i];
        }
    }

    return monsterId;
}
