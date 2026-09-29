#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct SetStoryStageRecord {
    u32 dwOpcode;
    u8 bStage;
} SetStoryStageRecord;

void RoomScriptOpSetStoryStage(SetStoryStageRecord *pRecord)
{
    g_abQuestEventState[0] = pRecord->bStage;
}
