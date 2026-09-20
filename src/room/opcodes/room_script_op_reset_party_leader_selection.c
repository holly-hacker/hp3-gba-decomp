#include "types.h"
#include "overworld.h"
#include "room_script.h"

void RoomScriptOpResetPartyLeaderSelection(RoomScriptRecord *pRecord)
{
    CyclePartyLeaderSelection_candidate(g_pPlayerObject, 2);
}
