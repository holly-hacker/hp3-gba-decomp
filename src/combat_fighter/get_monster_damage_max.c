#include "types.h"
#include "combat_fighter.h"

u32 GetMonsterDamageMax(u32 monster)
{
    return MonsterTable[monster].wDamageMax;
}
