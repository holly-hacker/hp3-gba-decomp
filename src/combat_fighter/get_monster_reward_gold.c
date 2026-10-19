#include "types.h"
#include "combat_fighter.h"

s32 GetMonsterRewardGold(u32 monster)
{
    return MonsterTable[monster].wRewardGold;
}
