#pragma once

#include "types.h"
#include "pscreen_folio_universitas.h"
#include "game_state.h"
#include "combat.h"
#include "../items.h"

// Reward ids share one number space with item ids: 0x00-0x4F are items,
// 0x50-0x82 are Folio Universitas cards (id - 0x50 is the card index), 0x83
// is Sickles, and any higher id indexes g_ItemInventory.abQuantities like an item.
#define REWARD_ID_FIRST_CARD 0x50
#define REWARD_ID_GOLD (REWARD_ID_FIRST_CARD + FOLIO_UNIVERSITAS_CARD_COUNT)
#define MAX_ITEM_QUANTITY 250

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

    if (MAX_ITEM_QUANTITY - amount < g_ItemInventory.abQuantities[rewardId])
        amount = MAX_ITEM_QUANTITY - g_ItemInventory.abQuantities[rewardId];
    g_ItemInventory.abQuantities[rewardId] = g_ItemInventory.abQuantities[rewardId] + amount;
    return g_ItemInventory.abQuantities[rewardId];
}
