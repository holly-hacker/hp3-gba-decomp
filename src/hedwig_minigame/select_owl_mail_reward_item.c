#include "types.h"
#include "constants/items.h"
#include "items.h"
#include "random.h"
#include "hedwig_minigame.h"

// The equipment or potion with the highest buy price below budget, ties
// broken at random; the Bracelet when none is cheap enough.
u32 SelectOwlMailRewardItem(s32 budget)
{
    s32 bestPrice = -1;
    u32 best = ITEM_BRACELET;
    u32 item;
    s32 price;

    for (item = 0; item <= ITEM_ANTI_PARALYSIS_POTION; item++)
    {
        price = GetItemBuyPrice(item);
        if (price < budget && (bestPrice < price || (bestPrice == price && Mt19937Chance(50))))
        {
            bestPrice = price;
            best = item;
        }
    }

    return best;
}
