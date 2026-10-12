#include "types.h"
#include "buckbeak_minigame.h"

// Whether the ring's on-screen position covers Buckbeak's and lies just ahead of him.
u32 HasBuckbeakMinigameRingBeenReached(u32 index)
{
    BuckbeakMinigameScreenPos ring = g_pBuckbeakMinigame->aRings[index].point.screen;
    BuckbeakMinigameScreenPos player = g_pBuckbeakMinigame->player.screen;
    s32 dx = ring.xy.x - player.xy.x;
    s32 dy;

    if (dx < 0)
        dx = -dx;
    if (dx > 0x3BFFFF)
        return 0;

    dy = ring.xy.y - player.xy.y;
    if (dy < 0)
        dy = -dy;
    if (dy > 0x3BFFFF)
        return 0;

    if (ring.dwDepth < player.dwDepth + 0xA0000 && ring.dwDepth > player.dwDepth)
        return 1;

    return 0;
}
