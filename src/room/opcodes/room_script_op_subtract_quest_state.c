#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct SubtractQuestStateRecord {
    u32 dwOpcode;
    u8 bAmount;
    u8 bIndex;
} SubtractQuestStateRecord;

void RoomScriptOpSubtractQuestState(SubtractQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bIndex] -= pRecord->bAmount;
}
