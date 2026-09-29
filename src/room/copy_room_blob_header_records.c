#include "types.h"
#include "overworld/room_blob.h"

// Copies the blob header into the runtime buffer; returns where the object table goes.
u8 *CopyRoomBlobHeaderRecords_candidate(const RoomBlobHeader *pBlob, const RoomBlobSubBlock *pVariant)
{
    u16 i;
    u16 size;

    g_pRoomTableBuffer->wRecordCount = pBlob->wRecordCount;
    for (i = 0; i < g_pRoomTableBuffer->wRecordCount; i++)
        g_pRoomTableBuffer->aRecords[i] = pBlob->aRecords[i];
    size = pBlob->wSize;
    g_pRoomTableBuffer->wSize = size;
    return (u8 *)g_pRoomTableBuffer + size;
}
