#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 GetItemCategory(u32 item)
{
    return g_pItemTable[item].dwCategory;
}
