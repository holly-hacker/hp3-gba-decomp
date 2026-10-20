#include "types.h"
#include "flipbook.h"

// Registers an animation of set bSet at (x, y); its first step shows on the next tick.
void AddRoomTileAnimation(u8 bSet, s32 x, s32 y, u8 bFlags)
{
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].bSet = bSet;
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].bStep = 0;
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].bDelay = 1;
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].bFlags = bFlags;
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].wX = x;
    g_aRoomTileAnimations[g_dwRoomTileAnimationCount].wY = y;
    g_dwRoomTileAnimationCount++;
}
