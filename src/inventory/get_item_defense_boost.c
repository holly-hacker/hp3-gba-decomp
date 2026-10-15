#include "types.h"
#include "game/items.h"
#include "inventory.h"

s32 GetItemDefenseBoost(u32 item)
{
    return g_pItemTable[item].stats.equipment.nDefenseX2 / 2;
}
