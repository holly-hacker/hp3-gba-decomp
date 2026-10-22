#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "spongify_pad_actor.h"

// Room actor constructor for tile actorType 10, a Spongify pad that launches the
// party to a target point.
Actor *SpawnSpongifyPadActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordSpongifyPad *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_SpongifyPad);
    u32 i;

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic
                      | ActorFlagUnk2000;
    SetActorActionState(pActor, 0);
    SetActorActionSubState(pActor, 1);
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickSpongifyPadActor;
    pActor->apfnCollisionCallback[0] = HandleSpongifyPadTouch;
    pActor->wCharacterId_candidate = pRecord->bVariant;
    SPONGIFY_PAD_STATE(pActor)->target.x = pRecord->nArg8;
    SPONGIFY_PAD_STATE(pActor)->target.y = pRecord->nArgA;
    SPONGIFY_PAD_STATE(pActor)->bRespawnRow = pRecord->abArgD[0];
    SPONGIFY_PAD_STATE(pActor)->bChainRow = pRecord->abArgD[1];
    SPONGIFY_PAD_STATE(pActor)->dwArmed = 0;
    SetActorPendingPalette(pActor, g_apRoomSpongifyPadEffectData[pActor->wCharacterId_candidate]);
    SetActorAnimData(pActor, g_apRoomSpongifyPadAnimFrames[pActor->wCharacterId_candidate], (void *)g_abRoomSpongifyPadAnimData, 0);
    pActor->oam.priority = 3;
    pActor->bDepthSortBias = 0x80;

    for (i = 0; i < ARRAY_COUNT(g_adwPartyMemberArrived); i++)
        g_adwPartyMemberArrived[i] = 0;

    return pActor;
}
