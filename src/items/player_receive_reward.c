#include "types.h"
#include "game/rewards.h"
#include "mt19937.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

// Stops the player, starts the receive-item action showing rewardId and
// grants one of it, or 30-60 Sickles.
void PlayerReceiveReward(u32 rewardId)
{
    u32 amount;

    CancelObjectMove_candidate(g_pPlayerObject);
    g_pPlayerObject->anim.bAnimFrameCounter = 0;
    SetObjectActionState(g_pPlayerObject, 0x17);
    SetObjectActionSubState(g_pPlayerObject, 0);
    g_pPlayerObject->dwStateTimer = 1;
    g_pPlayerObject->bReceivedRewardId = rewardId;

    if (rewardId == REWARD_ID_GOLD)
        amount = Mt19937RandRange(30, 60);
    else
        amount = 1;
    GrantReward(rewardId, amount);
}
