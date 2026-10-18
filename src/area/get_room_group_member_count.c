#include "types.h"
#include "area.h"

// Number of records in actor group `row`.
u16 GetRoomGroupMemberCount(u8 row)
{
    RoomBlobTable *pGroup;

    pGroup = (RoomBlobTable *)((u8 *)g_pRoomActorTable + g_pRoomActorTable->awOffsets[row]);
    return pGroup->wCount;
}
