#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"
#include "screen_transitions.h"

void RoomScriptOpPlayScreenTransitionIn(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionInByIndex(0x3f, 2);
}
