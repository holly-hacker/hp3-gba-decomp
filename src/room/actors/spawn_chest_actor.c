#include "types.h"
#include "overworld/room_actor.h"
#include "gen/graphics/overworld.h"

// Room actor constructor for tile actorType 9, the chest.
// See docs/formats/rooms.md.
Actor *SpawnChestActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk9 *pRecord = sub_08005C38(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_Chest);
    u32 kind;
    u32 mask;
    u8 index;
    u32 flagId;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x04002015;
    SetActorActionState(pActor, 0);
    SetActorActionSubState(pActor, 1);
    pActor->bUnk_0x7C = 1;
    pActor->anim.bAnimFrameDelay = 1;
    // The flag id is kept in the actor script PC slot.
    pActor->scriptState.wScriptPc = pRecord->wFlagId;
    kind = pRecord->bKind;
    pActor->modeState.chest.bKind = kind;
    pActor->modeState.chest.wRewardId = pRecord->bRewardId;
    pActor->modeState.chest.pair.bytes.bRespawnGroup = pRecord->bRespawnGroup;
    pActor->modeState.chest.pair.bytes.bChain = pRecord->bChain;

    flagId = pActor->scriptState.wScriptPc;
    index = flagId >> 3;
    mask = 1 << (flagId & 7);

    if (g_abOpenedChestFlags[index] & mask)
        pActor->modeState.chest.bOpened = 1;

    pActor->pfnTick = TickChestActor;
    pActor->apfnCollisionCallback[0] = HandleChestTouch;
    SetActorPendingPalette(pActor, gChestPalette);
    pActor->modeState.chest.bUnk67 = 0;
    pActor->modeState.chest.bUnchaining = 0;

    // Kind 2 spawns hidden and untouchable.
    if (kind == 2)
        pActor->dwFlags &= ~(ActorFlagVisible | ActorFlagWantsCollisionCheck);

    if (pActor->modeState.chest.bOpened != 0)
    {
        if (kind == 2)
            pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        else
            SetActorAnimData(pActor, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 8);
    }
    else
    {
        SetActorAnimData(pActor, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 0);
    }

    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    return pActor;
}
