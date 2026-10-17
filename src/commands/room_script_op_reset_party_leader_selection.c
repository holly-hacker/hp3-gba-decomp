#include "commands.h"
#include "overworld/room_script.h"
#include "hero.h"

void RoomScriptOpResetPartyLeaderSelection(RoomScriptRecord *pRecord)
{
    CyclePartyLeaderSelection_candidate(g_pPlayerActor, 2);
}
