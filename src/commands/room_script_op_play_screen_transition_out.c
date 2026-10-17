#include "commands.h"
#include "overworld/room_script.h"
#include "screen_transitions.h"

void RoomScriptOpPlayScreenTransitionOut(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
