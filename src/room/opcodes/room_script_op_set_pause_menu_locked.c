#include "types.h"
#include "overworld.h"
#include "room_script.h"

void RoomScriptOpSetPauseMenuLocked(RoomScriptRecord *pRecord)
{
    g_dwPauseMenuLocked = pRecord->operand.ab[0];
}
