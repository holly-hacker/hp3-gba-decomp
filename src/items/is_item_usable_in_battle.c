#include "types.h"
#include "game/items.h"
#include "items.h"

u32 IsItemUsableInBattle(u32 item)
{
    return g_pItemTable[item].dwFlags & 1;
}
