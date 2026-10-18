#include "types.h"
#include "area.h"
#include "hero.h"

// Live actor of record (x, y); (0, 0xFF) selects the player slot instead.
Actor *GetRoomActorPtr(u8 x, u8 y)
{
    RoomBlobTable *pGroup;
    RoomActorRecord *pRecord;
    u8 slot;

    if (x == 0 && y > 0xFE)
    {
        slot = 0xFF - y;
        return g_OverworldControlState.aSlots[slot].pActor;
    }

    pGroup = (RoomBlobTable *)((u8 *)g_pRoomActorTable + g_pRoomActorTable->awOffsets[x]);
    pRecord = (RoomActorRecord *)((u8 *)pGroup + pGroup->awOffsets[y]);
    return pRecord->pActor;
}
