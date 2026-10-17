#include "types.h"
#include "commands.h"
#include "random.h"

typedef struct SetRandomQuestStateRecord {
    u32 dwOpcode;
    s16 nMin;
    s16 nMax;
    u8 bIndex;
} SetRandomQuestStateRecord;

void RoomScriptOpSetRandomQuestState(SetRandomQuestStateRecord *pRecord)
{
    g_abQuestEventState[pRecord->bIndex] = Mt19937RandRange(pRecord->nMin, pRecord->nMax);
}
