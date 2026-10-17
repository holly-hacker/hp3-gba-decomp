#include "types.h"
#include "game/items.h"
#include "items.h"

s32 GetPotionMagnitude(s32 item)
{
    return g_pItemTable[item].stats.potion.nMagnitude;
}
