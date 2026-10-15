#include "types.h"
#include "game/items.h"
#include "inventory.h"

s32 GetItemMagicDefense(u32 item)
{
    return g_pItemTable[item].nMagicDefense;
}
