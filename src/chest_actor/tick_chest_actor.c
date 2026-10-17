#include "types.h"
#include "area.h"
#include "chest_actor.h"
#include "game/rewards.h"
#include "sound.h"
#include "overworld/overworld.h"
#include "overworld/room_actor.h"
#include "overworld/room_script.h"
#include "hero.h"

// Per-frame tick of a chest (room actor type 9). HandleChestTouch starts the
// opening in action substate 8; see docs/formats/rooms.md.
void TickChestActor(Actor *pActor)
{
    u8 kind = pActor->modeState.chest.bKind;
    u32 flagId;
    u8 index;
    u8 mask;

    switch (pActor->bActionSubState)
    {
    case 1:
        // Idle: HandleChestTouch starts the opening.
        break;

    case 5:
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;

    case 8:
        PlaySoundById(0x1d);
        SetActorActionSubState(pActor, 11);
        SetActorAnimData(pActor, g_apRoomChestAnimFrames[kind], g_abRoomChestAnimData[kind], 2);
        break;

    case 11:
        // When the opening animation ends, grant the reward and mark the
        // chest opened.
        if (pActor->dwFlags & ActorFlagActionAnimDone)
        {
            if (pActor->modeState.chest.wRewardId <= REWARD_ID_GOLD)
                PlayerReceiveReward(pActor->modeState.chest.wRewardId);
            else if (pActor->modeState.chest.pair.wPair != 0)
                RespawnGroupAndRunChain(pActor->modeState.chest.pair.bytes.bRespawnGroup,
                                                pActor->modeState.chest.pair.bytes.bChain);
            SetActorActionSubState(pActor, 10);
            pActor->dwStateTimer = 0;
            flagId = pActor->scriptState.wScriptPc;
            index = flagId >> 3;
            mask = 1 << (flagId & 7);
            g_abOpenedChestFlags[index] |= mask;
        }
        break;

    case 10:
        // After 12 more frames, release the player and run the pair.
        if (pActor->dwStateTimer++ > 11)
        {
            SetActorActionState(g_pPlayerActor, 0x21);
            SetActorPrevActionState(g_pPlayerActor, 0x21);
            pActor->dwStateTimer = 0;
            SetActorActionSubState(pActor, 1);
            if (pActor->modeState.chest.pair.wPair != 0)
                RespawnGroupAndRunChain(pActor->modeState.chest.pair.bytes.bRespawnGroup,
                                                pActor->modeState.chest.pair.bytes.bChain);
        }
        break;
    }
}
