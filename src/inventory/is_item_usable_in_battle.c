#include "types.h"
#include "game/items.h"
#include "inventory.h"

u32 IsItemUsableInBattle_candidate(u32 item)
{
    return g_pItemTable[item].dwFlags & 1;
}
