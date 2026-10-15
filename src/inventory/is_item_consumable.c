#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 IsItemConsumable(s32 item)
{
    return (g_pItemTable[item].dwFlags >> 2) & 1;
}
