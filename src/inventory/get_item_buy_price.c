#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 GetItemBuyPrice(u32 item)
{
    return g_pItemTable[item].nBuyPrice;
}
