#include "types.h"
#include "game/items.h"
#include "items.h"

s32 GetItemAgility(u32 item)
{
    return g_pItemTable[item].stats.equipment.nAgility;
}
