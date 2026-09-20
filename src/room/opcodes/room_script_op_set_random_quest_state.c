#include "types.h"
#include "mt19937.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpSetRandomQuestState(RoomScriptRecord *pRecord)
{
    g_abQuestEventState[pRecord->operand.ab[4]] = Mt19937RandRange(pRecord->operand.asw[0], pRecord->operand.asw[1]);
}
