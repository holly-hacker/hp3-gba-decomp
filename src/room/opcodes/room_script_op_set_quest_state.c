#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct SetQuestStateRecord {
    u32 dwOpcode;
    u8 bValue;
    u8 bIndex;
} SetQuestStateRecord;

void RoomScriptOpSetQuestState(SetQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bIndex] = pRecord->bValue;
}
