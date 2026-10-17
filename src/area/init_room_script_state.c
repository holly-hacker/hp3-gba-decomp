#include "types.h"
#include "area.h"
#include "mem.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_blob.h"
#include "overworld/room_script.h"
#include "commands.h"
#include "trigger_actor.h"

void InitRoomScriptState(void)
{
    g_dwRoomScriptRunState = 0;
    g_pRoomTableBuffer = AllocBlock(0x2200);
    g_abQuestEventState[QUEST_STORY_STAGE] = 0;
    g_bRestoringRoomActors_candidate = 0;
}
