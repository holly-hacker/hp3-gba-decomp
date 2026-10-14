#include "types.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 10, a Spongify pad that launches the
// party to a target point. See docs/formats/rooms.md.
Actor *SpawnSpongifyPadActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnkA *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_UnkA);
    u32 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = 0x200D;
    SetActorActionState(pActor, 0);
    SetActorActionSubState(pActor, 1);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = sub_08040114;
    pActor->apfnCollisionCallback[0] = sub_08040358;
    pActor->wCharacterId_candidate = pRecord->bVariant;
    ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->nArg8;
    ROOM_ACTOR_WORD_STATE(pActor)->n64 = pRecord->nArgA;
    ROOM_ACTOR_WORD_STATE(pActor)->b6C = pRecord->abArgD[0];
    ROOM_ACTOR_WORD_STATE(pActor)->b6D = pRecord->abArgD[1];
    ROOM_ACTOR_WORD_STATE(pActor)->n68 = 0;
    SetActorPendingPalette(pActor, g_apRoomSpongifyPadEffectData[pActor->wCharacterId_candidate]);
    SetActorAnimData(pActor, g_apRoomSpongifyPadAnimFrames[pActor->wCharacterId_candidate], (void *)g_abRoomSpongifyPadAnimData, 0);
    pActor->oam.priority = 3;
    pActor->bDepthSortBias = 0x80;

    for (i = 0; i < ARRAY_COUNT(g_adwRoomActorUnkACState); i++)
        g_adwRoomActorUnkACState[i] = 0;

    return pActor;
}
