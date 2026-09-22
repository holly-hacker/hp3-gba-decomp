#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpPlayScreenTransitionOut(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
