#include "types.h"
#include "overworld/room.h"
#include "flipbook.h"

u32 GetRoomTileAnimFrameBlockCount(const RoomTileAnimation *pAnim)
{
    return g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->wBlockCount;
}
