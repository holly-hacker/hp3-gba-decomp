#include "types.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 11, a flame jet that cycles on and
// off. See docs/formats/rooms.md.
Actor *SpawnFlamePillarActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnkB *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_UnkB);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic | ActorFlagHasAnimation;
    SetActorActionState(pActor, 4);
    SetActorActionSubState(pActor, 0);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = sub_08044960;
    pActor->apfnCollisionCallback[0] = sub_08044ADC;
    pActor->wCharacterId_candidate = pRecord->abArgC[0];
    pActor->modeState.actor.bRoomScriptArg64_candidate = pRecord->abArgC[1];
    pActor->modeState.actor.bFollowResumeDistance = pRecord->abArgC[2];
    pActor->scriptState.wScriptPc = pRecord->wArg8;
    pActor->modeState.actor.wStagedDamage = pRecord->wArgA;
    SetActorPendingPalette(pActor, g_apRoomFlamePillarEffectData[pActor->wCharacterId_candidate]);
    SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wCharacterId_candidate], (void *)g_abRoomFlamePillarAnimData, 0);
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    return pActor;
}
