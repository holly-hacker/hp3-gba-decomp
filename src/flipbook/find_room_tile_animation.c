#include "types.h"
#include "flipbook.h"

// Returns the animation registered at (x, y), or NULL.
RoomTileAnimation *FindRoomTileAnimation(s32 x, s32 y)
{
    u32 i;

    for (i = 0; i < g_dwRoomTileAnimationCount; i++)
    {
        if (g_aRoomTileAnimations[i].wX == x && g_aRoomTileAnimations[i].wY == y)
            return &g_aRoomTileAnimations[i];
    }

    return NULL;
}
