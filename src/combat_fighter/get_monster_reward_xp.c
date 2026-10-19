#include "types.h"
#include "combat_fighter.h"

s32 GetMonsterRewardXp(u32 monster)
{
    return MonsterTable[monster].wRewardXp;
}
