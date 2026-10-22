#include "types.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "invisible_actors.h"

// Per-frame tick of a trigger zone (RoomActorType_TriggerZone or
// RoomActorType_TriggerRect). The collision callbacks fire it from idle state 0:
// state 4 runs the record's pair and re-arms after the delay, state 5 runs it and
// frees the zone.
void TickTriggerZoneActor(Actor *pActor)
{
    RoomActorRecordTriggerZone *pRecord;

    switch (pActor->bActionState)
    {
    case 0:
        // Idle until a collision callback fires it.
        break;

    case 1:
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;

    case 3:
        // Re-arm once the delay runs out.
        if (--pActor->dwStateTimer == -1)
        {
            pActor->dwFlags |= ActorFlagWantsCollisionCheck;
            SetActorActionState(pActor, 0);
        }
        break;

    case 4:
        pRecord = GetRoomActorStaticRecord(pActor->bRoomTileCol_candidate, pActor->bRoomTileRow_candidate);
        if (pActor->wActorType == RoomActorType_TriggerRect)
            RespawnGroupAndRunChain(((RoomActorRecordTriggerRect *)pRecord)->bRespawnGroup,
                                    ((RoomActorRecordTriggerRect *)pRecord)->bChain);
        else
            RespawnGroupAndRunChain(pRecord->bRespawnGroup, pRecord->bChain);
        pActor->dwStateTimer = ROOM_ACTOR_WORD_STATE(pActor)->n60;
        SetActorActionState(pActor, 3);
        break;

    case 5:
        pRecord = GetRoomActorStaticRecord(pActor->bRoomTileCol_candidate, pActor->bRoomTileRow_candidate);
        if (pActor->wActorType == RoomActorType_TriggerRect)
            RespawnGroupAndRunChain(((RoomActorRecordTriggerRect *)pRecord)->bRespawnGroup,
                                    ((RoomActorRecordTriggerRect *)pRecord)->bChain);
        else
            RespawnGroupAndRunChain(pRecord->bRespawnGroup, pRecord->bChain);
        SetActorActionState(pActor, 1);
        break;
    }
}
