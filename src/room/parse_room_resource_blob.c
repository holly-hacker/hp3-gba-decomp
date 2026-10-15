#include "types.h"
#include "mem.h"
#include "overworld/overworld.h"
#include "overworld/room_blob.h"

// Rebuilds the runtime room tables from a room's resource blob.
void ParseRoomResourceBlob(const RoomBlobHeader *pBlob)
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
    pTable = (u8 *)pBlob + pStageIndex->aEntries[pStageIndex->abStageToVariant[g_abQuestEventState[QUEST_STORY_STAGE]]].wSubBlockOffset;
    pVariant = (const RoomBlobSubBlock *)pTable;

    pTable = CopyRoomBlobHeaderRecords(pBlob, pVariant);
    g_pRoomActorTable = (RoomBlobTable *)pTable;
    pTable = BuildRoomActorTable(pDefault, pVariant, pTable);
    g_pRoomRouteTable = (RoomBlobTable *)pTable;
    pTable = BuildRoomRouteTable(pDefault, pVariant, pTable);
    g_pRoomScriptChainTable = (RoomScriptTable *)pTable;
    BuildRoomScriptChainTable(pDefault, pVariant, pTable);
}
