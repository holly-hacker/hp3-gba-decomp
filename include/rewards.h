#pragma once

#include "types.h"
#include "folio_universitas.h"
#include "items.h"
#include "save.h"

// Rewards earned this battle, paid out by the victory screen. The XP total is
// one pool shared by the whole party; reward grants also stage their Sickles
// amount in the gold variable.
extern u16 g_nBattleXpReward;    // 0x0300260E
extern u16 g_nBattleGoldReward;  // 0x03002610

// Reward ids share one number space with item ids: 0x00-0x4F are items,
// 0x50-0x82 are Folio Universitas cards (id - 0x50 is the card index), 0x83
// is Sickles, and any higher id indexes g_abItemQuantities like an item.
#define REWARD_ID_FIRST_CARD 0x50
#define REWARD_ID_GOLD (REWARD_ID_FIRST_CARD + FOLIO_UNIVERSITAS_CARD_COUNT)
#define MAX_ITEM_QUANTITY 250

// Gives `amount` of a reward and returns how many of it the player now has:
// the Sickles total, a card's copy count (amount is ignored), or the item
// count, capped at MAX_ITEM_QUANTITY.
u32 GrantReward(s32 rewardId, u32 amount);

// The same logic as GrantReward, for functions that carry their own inlined
// copy of it. Keep the two in sync.
static inline u32 GrantRewardInline(s32 rewardId, u32 amount)
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
