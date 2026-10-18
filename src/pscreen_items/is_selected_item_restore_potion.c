#include "types.h"
#include "pscreen_items.h"
#include "items.h"
#include "game/items.h"

u32 IsSelectedItemRestorePotion(void)
{
    switch (GetPotionEffect(GetItemListSelection()))
    {
    case PotionEffectStamina:
    case PotionEffectMagic:
        return 1;

    case 0:
    case PotionEffectPoison:
    case PotionEffectParalysis:
    default:
        return 0;
    }
}
