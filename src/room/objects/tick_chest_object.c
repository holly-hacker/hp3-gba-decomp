#include "types.h"
#include "game/rewards.h"
#include "graphics/audio.h"
#include "overworld/overworld.h"
#include "overworld/room_object.h"
#include "overworld/room_script.h"

// Per-frame tick of a chest (room object type 9). HandleChestTouch starts the
// opening in action substate 8; see docs/formats/rooms.md.
void TickChestObject(Object *pObj)
{
    u8 kind = pObj->modeState.chest.bKind;
    u32 flagId;
    u8 index;
    u8 mask;

    switch (pObj->bActionSubState)
    {
    case 1:
        // Idle: HandleChestTouch starts the opening.
        break;

    case 5:
        if (pObj->pLinkedObject_candidate != NULL)
            pObj->pLinkedObject_candidate->dwFlags |= ObjectFlagPendingDestroy | ObjectFlagAnimFrameLoaded;
        pObj->dwFlags |= ObjectFlagPendingDestroy | ObjectFlagAnimFrameLoaded;
        break;

    case 8:
        PlaySoundById(0x1d);
        SetObjectActionSubState(pObj, 11);
        SetObjectAnimData(pObj, g_apRoomChestAnimFrames[kind], g_abRoomChestAnimData[kind], 2);
        break;

    case 11:
        // When the opening animation ends, grant the reward and mark the
        // chest opened.
        if (pObj->dwFlags & ObjectFlagActionAnimDone)
        {
            if (pObj->modeState.chest.wRewardId <= REWARD_ID_GOLD)
                PlayerReceiveReward(pObj->modeState.chest.wRewardId);
            else if (pObj->modeState.chest.pair.wPair != 0)
                RespawnRowAndRunChain_candidate(pObj->modeState.chest.pair.bytes.bRespawnGroup,
                                                pObj->modeState.chest.pair.bytes.bChain);
            SetObjectActionSubState(pObj, 10);
            pObj->dwStateTimer = 0;
            flagId = pObj->scriptState.wScriptPc;
            index = flagId >> 3;
            mask = 1 << (flagId & 7);
            g_abOpenedChestFlags[index] |= mask;
        }
        break;

    case 10:
        // After 12 more frames, release the player and run the pair.
        if (pObj->dwStateTimer++ > 11)
        {
            SetObjectActionState(g_pPlayerObject, 0x21);
            SetObjectAnimSubState_candidate(g_pPlayerObject, 0x21);
            pObj->dwStateTimer = 0;
            SetObjectActionSubState(pObj, 1);
            if (pObj->modeState.chest.pair.wPair != 0)
                RespawnRowAndRunChain_candidate(pObj->modeState.chest.pair.bytes.bRespawnGroup,
                                                pObj->modeState.chest.pair.bytes.bChain);
        }
        break;
    }
}
