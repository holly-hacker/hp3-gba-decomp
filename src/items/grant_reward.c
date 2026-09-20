#include "types.h"
#include "rewards.h"

// Gives `amount` of a reward id and returns how many of it the player now
// has: the Sickles total, a card's copy count, or the item count.
u32 GrantReward(s32 rewardId, u32 amount)
{
    if (rewardId == REWARD_ID_GOLD)
    {
        g_nBattleGoldReward = amount;
        return AddSickles(g_nBattleGoldReward);
    }

    if (rewardId >= REWARD_ID_FIRST_CARD && rewardId < REWARD_ID_GOLD)
        return IncrementFolioUniversitasCard(rewardId - REWARD_ID_FIRST_CARD);

    if (MAX_ITEM_QUANTITY - amount < g_abItemQuantities[rewardId])
        amount = MAX_ITEM_QUANTITY - g_abItemQuantities[rewardId];
    g_abItemQuantities[rewardId] = g_abItemQuantities[rewardId] + amount;
    return g_abItemQuantities[rewardId];
}
