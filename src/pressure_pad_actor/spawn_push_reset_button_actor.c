#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "pressure_pad_actor.h"

// Room actor constructor for tile actorType 8, a button that a spell presses to
// respawn a push puzzle's actors. See docs/formats/rooms.md.
Actor *SpawnPushResetButtonActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk8 *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_Unk8);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->oam.objMode = 0;
    pActor->oam.bpp8 = 0;
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0xFF;
    pActor->wCharacterId_candidate = pRecord->bVariant;
    pActor->anim.bAnimFrameDelay = 0;
    pActor->pfnTick = sub_08035664;
    pActor->apfnCollisionCallback[0] = sub_08035724;
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[0] = pRecord->abPairs[0];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[0] = pRecord->abPairs[1];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[1] = pRecord->abPairs[2];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[1] = pRecord->abPairs[3];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[2] = pRecord->abPairs[4];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[2] = pRecord->abPairs[5];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[3] = pRecord->abPairs[6];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[3] = pRecord->abPairs[7];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[4] = pRecord->abPairs[8];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[4] = pRecord->abPairs[9];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[5] = pRecord->abPairs[10];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[5] = pRecord->abPairs[11];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[6] = pRecord->abPairs[12];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[6] = pRecord->abPairs[13];
    ROOM_ACTOR_UNK8_STATE(pActor)->abA[7] = pRecord->abPairs[14];
    ROOM_ACTOR_UNK8_STATE(pActor)->abB[7] = pRecord->abPairs[15];
    pActor->dwFlags = 0x0400221D;
    SetActorPendingPalette(pActor, g_apRoomActorUnk8EffectData[pActor->wCharacterId_candidate]);
    SetActorAssetRecord(pActor, g_apRoomActorUnk8AssetRecords[pActor->wCharacterId_candidate]);
    SetActorAnimFrame(pActor, 0);
    SetActorActionState(pActor, 0);
    return pActor;
}
