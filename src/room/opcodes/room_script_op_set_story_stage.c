#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct SetStoryStageRecord {
    u32 dwOpcode;
    u8 bStage;
} SetStoryStageRecord;

void RoomScriptOpSetStoryStage(SetStoryStageRecord *pRecord)
{
    g_abQuestEventState[0] = pRecord->bStage;
}
