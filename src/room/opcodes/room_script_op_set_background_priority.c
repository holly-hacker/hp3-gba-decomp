#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpSetBackgroundPriority(RoomScriptRecord *pRecord)
{
    SetBgPriority(pRecord->operand.ab[0], pRecord->operand.ab[1]);
}
