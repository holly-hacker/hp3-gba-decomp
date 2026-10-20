#include "types.h"
#include "flipbook.h"

// Resumes the animation at (x, y). One halted on a ROOM_TILE_ANIM_HALT frame moves
// past it, restarting the set if the following frame is ROOM_TILE_ANIM_LOOP.
void ResumeRoomTileAnimation(s32 x, s32 y)
{
    RoomTileAnimation *pAnim = FindRoomTileAnimation(x, y);

    pAnim->bFlags &= ~ROOM_TILE_ANIM_FLAG_HALTED;
    if (pAnim->bStep != 0)
    {
        pAnim->bStep++;
        pAnim->bDelay = GetRoomTileAnimFrameDelay(pAnim);
        if (pAnim->bDelay == ROOM_TILE_ANIM_LOOP)
        {
            pAnim->bStep = 0;
            pAnim->bDelay = GetRoomTileAnimFrameDelay(pAnim);
        }
    }
}
