#include "types.h"
#include "commands.h"

typedef struct SubtractQuestStateRecord {
    u32 dwOpcode;
    u8 bAmount;
    u8 bIndex;
} SubtractQuestStateRecord;

void RoomScriptOpSubtractQuestState(SubtractQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bIndex] -= pRecord->bAmount;
}
