#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct SetDefeatWarpSelectorRecord {
    u32 dwOpcode;
    u8 bValue;
} SetDefeatWarpSelectorRecord;

void RoomScriptOpSetDefeatWarpSelector(SetDefeatWarpSelectorRecord *pRecord)
{
    g_abQuestEventState[QUEST_DEFEAT_WARP_SELECTOR] = pRecord->bValue;
}
