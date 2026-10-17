#include "types.h"
#include "game/items.h"
#include "items.h"

u32 GetItemSellPrice(u32 item)
{
    return g_pItemTable[item].nSellPrice;
}
