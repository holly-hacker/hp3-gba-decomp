#include "types.h"
#include "area.h"
#include "overworld/room_script.h"

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
                if (pActor->pLinkedActor_candidate != NULL)
                    pActor->pLinkedActor_candidate->dwFlags |= 0x82;
                pActor->dwFlags |= 0x82;
            }
        }
    }
}
