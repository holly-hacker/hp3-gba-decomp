#include "commands.h"
#include "overworld/room_script.h"
#include "hero.h"

void RoomScriptOpResetPartyLeaderSelection(RoomScriptRecord *pRecord)
{
    CycleSelectedFieldSpell(g_pPlayerActor, 2);
}
