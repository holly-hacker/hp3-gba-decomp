#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpPlayScreenTransitionIn(RoomScriptRecord *pRecord)
{
    PlayScreenTransitionInByIndex_candidate(0x3f, 2);
}
