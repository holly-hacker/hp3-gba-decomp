#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpClearQuestStateUpperHalf(RoomScriptRecord *pRecord)
{
    s32 i;

    for (i = 0x80; i <= 0xff; i++)
        g_abQuestEventState[i] = 0;
}
