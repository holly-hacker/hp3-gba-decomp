#include "types.h"
#include "area.h"
#include "event_actors.h"

// Copies room-script chain `index` record by record, up to and including its terminator.
u8 *CopyRoomScriptChain(const RoomBlobTable *pTable, u8 *pDst, u8 index)
{
    const u8 *pSrc;
    const RoomScriptRecord *pRecord;
    u16 step;
    u8 i;

    step = pTable->awOffsets[index];
    pSrc = (const u8 *)pTable + step;
    do
    {
        pRecord = (const RoomScriptRecord *)pSrc;
        step = g_abRoomScriptOpcodeLengths[pRecord->dwOpcode];
        for (i = 0; i < step; i++)
            *pDst++ = *pSrc++;
    } while (pRecord->dwOpcode != 0);
    return pDst;
}
