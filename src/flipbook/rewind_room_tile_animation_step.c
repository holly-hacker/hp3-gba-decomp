#include "types.h"
#include "flipbook.h"

// Steps back so the last shown step is shown again on the next tick. Returns 0
// (and changes nothing) when the animation is at its first step, otherwise 1.
u32 RewindRoomTileAnimationStep(RoomTileAnimation *pAnim)
{
    if (pAnim->bStep != 0)
    {
        pAnim->bStep--;
        pAnim->bDelay = 1;
        pAnim->bFlags &= ~ROOM_TILE_ANIM_FLAG_HALTED;
        return 1;
    }

    return 0;
}
