#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpHideBackgroundLayer(RoomScriptRecord *pRecord)
{
    DisableBg(pRecord->operand.ab[0]);
}
