#include "types.h"
#include "area.h"
#include "torch_actor.h"

// Room actor constructor for tile actorType 11, a flame jet that cycles on and
// off. See docs/formats/rooms.md.
Actor *SpawnFlamePillarActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnkB *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_FlamePillar);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic | ActorFlagHasAnimation;
    SetActorActionState(pActor, 4);
    SetActorActionSubState(pActor, 0);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickFlamePillarActor;
    pActor->apfnCollisionCallback[0] = HandleFlamePillarTouch;
    pActor->wCharacterId_candidate = pRecord->abArgC[0];
    pActor->modeState.flamePillar.touch.rows.bRespawnRow = pRecord->abArgC[1];
    pActor->modeState.flamePillar.touch.rows.bChainRow = pRecord->abArgC[2];
    pActor->scriptState.wFlameOutTicks = pRecord->wArg8;
    pActor->modeState.flamePillar.wLitTicks = pRecord->wArgA;
    SetActorPendingPalette(pActor, g_apRoomFlamePillarEffectData[pActor->wCharacterId_candidate]);
    SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wCharacterId_candidate], (void *)g_abRoomFlamePillarAnimData, 0);
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    return pActor;
}
