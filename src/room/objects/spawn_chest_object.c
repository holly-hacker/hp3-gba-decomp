#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

// Room object constructor for tile objType 9, the chest.
// See docs/formats/rooms.md.
Actor *SpawnChestObject(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk9 *pRecord = sub_08005C38(bColumn, bRow);
    Actor *pObj = AllocActorOfType(RoomObjectType_Chest);
    u32 kind;
    u32 mask;
    u8 index;
    u32 flagId;

    SnapActorPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x04002015;
    SetActorActionState(pObj, 0);
    SetActorActionSubState(pObj, 1);
    pObj->bUnk_0x7C = 1;
    pObj->anim.bAnimFrameDelay = 1;
    // The flag id is kept in the object script PC slot.
    pObj->scriptState.wScriptPc = pRecord->wFlagId;
    kind = pRecord->bKind;
    pObj->modeState.chest.bKind = kind;
    pObj->modeState.chest.wRewardId = pRecord->bRewardId;
    pObj->modeState.chest.pair.bytes.bRespawnGroup = pRecord->bRespawnGroup;
    pObj->modeState.chest.pair.bytes.bChain = pRecord->bChain;

    flagId = pObj->scriptState.wScriptPc;
    index = flagId >> 3;
    mask = 1 << (flagId & 7);

    if (g_abOpenedChestFlags[index] & mask)
        pObj->modeState.chest.bOpened = 1;

    pObj->pfnTick = TickChestObject;
    pObj->apfnCollisionCallback[0] = HandleChestTouch;
    SetObjectPendingPalette(pObj, gChestPalette);
    pObj->modeState.chest.bUnk67 = 0;
    pObj->modeState.chest.bUnchaining = 0;

    // Kind 2 spawns hidden and untouchable.
    if (kind == 2)
        pObj->dwFlags &= ~(ActorFlagVisible | ActorFlagWantsCollisionCheck);

    if (pObj->modeState.chest.bOpened != 0)
    {
        if (kind == 2)
            pObj->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        else
            SetActorAnimData(pObj, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 8);
    }
    else
    {
        SetActorAnimData(pObj, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 0);
    }

    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0x80;
    return pObj;
}
