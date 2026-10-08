#include "types.h"
#include "overworld/room.h"

// Shows the first step of a set at (x, y) once, without registering an animation.
void ApplyRoomTileAnimationAt(u8 bSet, u32 x, u32 y, u8 bFlags)
{
    RoomTileAnimation anim;

    anim.bSet = bSet;
    anim.bStep = 0;
    anim.bDelay = 1;
    anim.bFlags = bFlags;
    anim.wX = x;
    anim.wY = y;
    ApplyRoomTileAnimationFrame(&anim);
}
