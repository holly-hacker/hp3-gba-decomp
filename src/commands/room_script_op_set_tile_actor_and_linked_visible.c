#include "types.h"
#include "area.h"
#include "commands.h"

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
        if (pActor->pLinkedActor != NULL)
            pActor->pLinkedActor->dwFlags |= ActorFlagVisible;
    }
    else
    {
        pActor->dwFlags &= ~ActorFlagVisible;
        if (pActor->pLinkedActor != NULL)
            pActor->pLinkedActor->dwFlags &= ~ActorFlagVisible;
    }
}
