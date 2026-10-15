#include "types.h"
#include "constants/items.h"
#include "game/items.h"
#include "game/rewards.h"
#include "inventory.h"

u32 GetRewardNameStringId_candidate(u32 rewardId)
{
    if (rewardId == ITEM_REMOVE)
        return 0x3FD;  // "Remove"

    if (rewardId == REWARD_ID_GOLD)
        return 0x597;  // "Sickles:"

    if (rewardId >= REWARD_ID_FIRST_CARD && rewardId < REWARD_ID_GOLD)
        return rewardId - REWARD_ID_FIRST_CARD + 0x412;  // card names, from "Fulbert the Fearful"

    return g_pItemTable[rewardId].nNameTextId;
}
