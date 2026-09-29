#include "types.h"
#include "graphics/display.h"
#include "overworld/room_script.h"

void RoomScriptOpPlayScreenTransitionOut(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
