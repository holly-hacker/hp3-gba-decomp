#include "types.h"
#include "graphics/display.h"
#include "overworld/room.h"
#include "overworld/terrain.h"

// Shows the effect of a room switch state: the two states use consecutive effect ids.
void ApplyRoomSwitchEffect(u32 state)
{
    if (state != 0)
    {
        SetAlphaBlendTargets(4, 0x1F);
        ApplyRoomTileAnimationAt(0x18, 0xE0, 0x220, 0);
    }
    else
    {
        SetAlphaBlendTargets(5, 0x1F);
        ApplyRoomTileAnimationAt(0x19, 0xE0, 0x220, 0);
    }
}
