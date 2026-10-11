#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 11, a flame jet that cycles on and
// off. See docs/formats/rooms.md.
Actor *SpawnFlamePillarObject(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnkB *pRecord = sub_08005C38(bColumn, bRow);
    Actor *pObj = AllocActorOfType(RoomObjectType_UnkB);

    SnapActorPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic | ActorFlagHasAnimation;
    SetActorActionState(pObj, 4);
    SetActorActionSubState(pObj, 0);
    pObj->anim.bAnimFrameDelay = 1;
    pObj->pfnTick = sub_08044960;
    pObj->apfnCollisionCallback[0] = sub_08044ADC;
    pObj->wCharacterId_candidate = pRecord->abArgC[0];
    pObj->modeState.actor.bRoomScriptArg64_candidate = pRecord->abArgC[1];
    pObj->modeState.actor.bFollowResumeDistance = pRecord->abArgC[2];
    pObj->scriptState.wScriptPc = pRecord->wArg8;
    pObj->modeState.actor.wStagedDamage = pRecord->wArgA;
    SetObjectPendingPalette(pObj, g_apRoomFlamePillarEffectData[pObj->wCharacterId_candidate]);
    SetActorAnimData(pObj, g_apRoomFlamePillarAnimFrames[pObj->wCharacterId_candidate], (void *)g_abRoomFlamePillarAnimData, 0);
    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0x80;
    return pObj;
}
