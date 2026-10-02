#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

void RoomScriptOpClearQuestStateUpperHalf(RoomScriptRecord *pRecord)
{
    s32 i;

    for (i = QUEST_UPPER_HALF_FIRST; i <= 0xff; i++)
        g_abQuestEventState[i] = 0;
}
