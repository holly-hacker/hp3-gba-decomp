#include "types.h"
#include "game/items.h"
#include "items.h"

u32 IsItemListedInItemsMenu_candidate(u32 item)
{
    return (g_pItemTable[item].dwFlags >> 1) & 1;
}
