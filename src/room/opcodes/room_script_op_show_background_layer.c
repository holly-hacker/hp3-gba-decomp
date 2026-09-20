#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpShowBackgroundLayer(RoomScriptRecord *pRecord)
{
    EnableBg(pRecord->operand.ab[0]);
}
