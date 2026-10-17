#include "types.h"
#include "commands.h"
#include "overworld/room.h"

typedef struct SetStoryStageRecord {
    u32 dwOpcode;
    u8 bStage;
} SetStoryStageRecord;

void RoomScriptOpSetStoryStage(SetStoryStageRecord *pRecord)
{
    g_abQuestEventState[QUEST_STORY_STAGE] = pRecord->bStage;
}
