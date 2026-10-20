#include "types.h"
#include "flipbook.h"

void HaltRoomTileAnimation(s32 x, s32 y)
{
    FindRoomTileAnimation(x, y)->bFlags |= ROOM_TILE_ANIM_FLAG_HALTED;
}
