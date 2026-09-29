#include "types.h"
#include "hw/mem.h"
#include "overworld/overworld.h"
#include "overworld/room_blob.h"

// Rebuilds the runtime room tables from a room's resource blob.
void ParseRoomResourceBlob_candidate(const RoomBlobHeader *pBlob)
{
    const RoomBlobStageIndex *pStageIndex;
    const RoomBlobSubBlock *pDefault;
    const RoomBlobSubBlock *pVariant;
    u8 *pTable;

    g_dwRoomChainRanThisFrame_candidate = 0;
    memset(g_pRoomTableBuffer, 0, 0x2200);

    pTable = (u8 *)pBlob + pBlob->wSize;
    pStageIndex = (const RoomBlobStageIndex *)pTable;
    pTable = (u8 *)pBlob + pStageIndex->aEntries[0].wSubBlockOffset;
    pDefault = (const RoomBlobSubBlock *)pTable;
    pTable = (u8 *)pBlob + pStageIndex->aEntries[pStageIndex->abStageToVariant[g_abQuestEventState[0]]].wSubBlockOffset;
    pVariant = (const RoomBlobSubBlock *)pTable;

    pTable = CopyRoomBlobHeaderRecords_candidate(pBlob, pVariant);
    g_pRoomObjectTable = (RoomBlobTable *)pTable;
    pTable = BuildRoomObjectTable_candidate(pDefault, pVariant, pTable);
    g_pRoomWarpTriggerTable = (RoomBlobTable *)pTable;
    pTable = BuildRoomWarpTriggerTable_candidate(pDefault, pVariant, pTable);
    g_pRoomSwitchStateObjectTable = (RoomScriptTable *)pTable;
    BuildRoomSwitchStateObjectTable_candidate(pDefault, pVariant, pTable);
}
