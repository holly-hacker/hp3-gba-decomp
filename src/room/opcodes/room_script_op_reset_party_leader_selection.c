#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

void RoomScriptOpResetPartyLeaderSelection(RoomScriptRecord *pRecord)
{
    CyclePartyLeaderSelection_candidate(g_pPlayerObject, 2);
}
