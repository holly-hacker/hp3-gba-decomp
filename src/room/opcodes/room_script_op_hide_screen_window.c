#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpHideScreenWindow(RoomScriptRecord *pRecord)
{
    HideScreenWindow_candidate(pRecord->operand.ab[0]);
}
