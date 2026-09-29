#include "types.h"
#include "mt19937.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

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
