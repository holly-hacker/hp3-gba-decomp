#include "types.h"
#include "overworld/room.h"

// Records the room switch state and returns nonzero if it changed.
u32 SetRoomSwitchState(u32 state)
{
    u32 changed;

    if (g_bRoomSwitchState == state)
        changed = 0;
    else
    {
        g_bRoomSwitchState = state;
        changed = 1;
    }

    return changed;
}

u32 GetRoomSwitchState(void)
{
    return g_bRoomSwitchState;
}
