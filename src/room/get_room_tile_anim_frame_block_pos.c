#include "types.h"
#include "overworld/room.h"

// Returns the pixel position of block index of the animation's current step.
void GetRoomTileAnimFrameBlockPos(const RoomTileAnimation *pAnim, u32 index, u16 *pX, u16 *pY)
{
    const RoomTileAnimBlock *pBlocks = g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->aBlocks;

    *pX = pBlocks[index].wX * 32;
    *pY = pBlocks[index].wY * 32;
}
