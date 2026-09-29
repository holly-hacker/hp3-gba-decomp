#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct CopyQuestStateRecord {
    u32 dwOpcode;
    u8 bSrcIndex;
    u8 bDstIndex;
} CopyQuestStateRecord;

void RoomScriptOpCopyQuestState(CopyQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bDstIndex] = g_abQuestEventState[pRecord->bSrcIndex];
}
