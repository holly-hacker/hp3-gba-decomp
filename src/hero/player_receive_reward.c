#include "types.h"
#include "game/rewards.h"
#include "items.h"
#include "mt19937.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "hero.h"

// Stops the player, starts the receive-item action showing rewardId and
// grants one of it, or 30-60 Sickles.
void PlayerReceiveReward(u32 rewardId)
{
    u32 amount;

    CancelActorMove_candidate(g_pPlayerActor);
    g_pPlayerActor->anim.bAnimFrameCounter = 0;
    SetActorActionState(g_pPlayerActor, 0x17);
    SetActorActionSubState(g_pPlayerActor, 0);
    g_pPlayerActor->dwStateTimer = 1;
    g_pPlayerActor->bReceivedRewardId = rewardId;

    if (rewardId == REWARD_ID_GOLD)
        amount = Mt19937RandRange(30, 60);
    else
        amount = 1;
    GrantReward(rewardId, amount);
}
