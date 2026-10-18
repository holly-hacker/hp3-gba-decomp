#include "types.h"
#include "area.h"

// The variant sub-block index the room blob uses at story stage questState.
u8 GetRoomBlobStageVariant(u8 questState, const void *pRoomResourceBlob)
{
    const RoomBlobHeader *pBlob;
    const RoomBlobStageIndex *pStageIndex;

    pBlob = pRoomResourceBlob;
    pStageIndex = (const RoomBlobStageIndex *)((const u8 *)pBlob + pBlob->wSize);
    return pStageIndex->abStageToVariant[questState];
}
