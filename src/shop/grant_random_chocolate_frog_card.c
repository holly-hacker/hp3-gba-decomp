#include "types.h"
#include "mt19937.h"
#include "rewards.h"
#include "shop.h"

// Grants one random card for a Chocolate Frog. The 30 rolls cover 10 card
// slots per category row, taking the first two cards of each 3-card combo:
// columns 0, 1, 3, 4, 6, 7 of rows 0-4. Third-of-combo cards, the rare tenth
// card of each category and the lone last card are never dealt.
u32 GrantRandomChocolateFrogCard(void)
{
    u32 roll;
    s32 rewardId;

    roll = Mt19937RandRange(0, 29);
    rewardId = REWARD_ID_FIRST_CARD;

    while (roll > 5)
    {
        rewardId += 10;
        roll -= 6;
    }

    while (roll > 1)
    {
        rewardId += 3;
        roll -= 2;
    }

    rewardId += roll;
    GrantRewardInline(rewardId, 1);

    return rewardId;
}
