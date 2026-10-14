#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorAndLinkedVisibleRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bVisible;
} SetTileActorAndLinkedVisibleRecord;

void RoomScriptOpSetTileActorAndLinkedVisible(SetTileActorAndLinkedVisibleRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bVisible != 0)
    {
        pActor->dwFlags |= ActorFlagVisible;
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->dwFlags |= ActorFlagVisible;
    }
    else
    {
        pActor->dwFlags &= ~ActorFlagVisible;
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->dwFlags &= ~ActorFlagVisible;
    }
}
