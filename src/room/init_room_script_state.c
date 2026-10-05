#include "types.h"
#include "hw/mem.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_blob.h"
#include "overworld/room_script.h"

void InitRoomScriptState_candidate(void)
{
    g_dwRoomScriptRunState = 0;
    g_pRoomTableBuffer = AllocBlock(0x2200);
    g_abQuestEventState[QUEST_STORY_STAGE] = 0;
    g_bRestoringRoomObjects_candidate = 0;
}
