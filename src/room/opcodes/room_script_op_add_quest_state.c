#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct AddQuestStateRecord {
    u32 dwOpcode;
    u8 bAmount;
    u8 bIndex;
} AddQuestStateRecord;

void RoomScriptOpAddQuestState(AddQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bIndex] += pRecord->bAmount;
}
