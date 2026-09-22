#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpPlayScreenTransitionIn(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionInByIndex(0x3f, 2);
}
