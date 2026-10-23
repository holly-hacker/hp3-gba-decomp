#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct DespawnRoomRowActorsRecord {
    u32 dwOpcode;
    u8 bRow;
} DespawnRoomRowActorsRecord;

void RoomScriptOpDespawnRoomRowActors(DespawnRoomRowActorsRecord *pRecord)
{
    u8 row = pRecord->bRow;
    u16 columnCount;
    u8 col;
    Actor *pActor;

    if (ShouldRunRoomIndex(row))
    {
        columnCount = GetRoomGroupMemberCount(row);
        for (col = 0; col < columnCount; col++)
        {
            pActor = GetRoomActorPtr(row, col);
            if (pActor != NULL)
            {
                if (pActor->pLinkedActor != NULL)
                    pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy
                                                               | ActorFlagAnimFrameLoaded;
                pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            }
        }
    }
}
