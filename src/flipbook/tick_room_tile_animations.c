#include "types.h"
#include "flipbook.h"

// Counts down each running animation's delay and shows its next step when it runs out.
// A delay of 0 holds the current step.
void TickRoomTileAnimations(void)
{
    u32 i;

    for (i = 0; i < g_dwRoomTileAnimationCount; i++)
    {
        if (g_aRoomTileAnimations[i].bDelay != 0
            && !(g_aRoomTileAnimations[i].bFlags & ROOM_TILE_ANIM_FLAG_HALTED))
        {
            if (--g_aRoomTileAnimations[i].bDelay == 0)
                ApplyRoomTileAnimationFrame(&g_aRoomTileAnimations[i]);
        }
    }
}
