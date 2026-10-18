#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script_bytecode.h"

// Stops the room-script VM, unless a walk is yielded on RSOP_StartBattle and
// resumes after the battle.
void StopRoomScriptChains(void)
{
    g_bRoomScriptCallStackDepth = 0;
    if (g_dwRoomScriptRunState != 2 || g_bRoomScriptYieldOpcode != RSOP_StartBattle)
    {
        g_dwRoomScriptRunState = 4;
        g_pRoomScriptYieldContinuation = NULL;
    }
}
