#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 11; see docs/formats/rooms.md.
Object *sub_08044894(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnkB *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_UnkB);

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = ObjectFlagVisible | ObjectFlagWantsCollisionCheck | ObjectFlagHasTickLogic | ObjectFlagHasAnimation;
    SetObjectActionState(pObj, 4);
    SetObjectActionSubState(pObj, 0);
    pObj->bAnimFrameDelay = 1;
    pObj->pfnTick = sub_08044960;
    pObj->apfnCollisionCallback[0] = sub_08044ADC;
    pObj->wCharacterId_candidate = pRecord->abArgC[0];
    pObj->modeState.actor.bRoomScriptArg64_candidate = pRecord->abArgC[1];
    pObj->modeState.actor.bFollowResumeDistance = pRecord->abArgC[2];
    pObj->scriptState.wScriptPc = pRecord->wArg8;
    pObj->modeState.actor.wStagedDamage = pRecord->wArgA;
    sub_08030844(pObj, g_apRoomObjUnkBEffectData[pObj->wCharacterId_candidate]);
    SetObjectAnimData(pObj, g_apRoomObjUnkBAnimFrames[pObj->wCharacterId_candidate], (void *)g_abRoomObjUnkBAnimData, 0);
    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0x80;
    return pObj;
}
