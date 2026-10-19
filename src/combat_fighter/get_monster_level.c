#include "types.h"
#include "combat_fighter.h"

u32 GetMonsterLevel(u32 monster)
{
    return MonsterTable[monster].bLevel;
}
