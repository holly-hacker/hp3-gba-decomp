#include "types.h"
#include "graphics/display.h"
#include "overworld/room_script.h"

void RoomScriptOpPlayScreenTransitionIn(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionInByIndex(0x3f, 2);
}
