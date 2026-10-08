#include "types.h"
#include "overworld/room.h"

u32 GetRoomTileAnimFrameLayerMask(const RoomTileAnimation *pAnim)
{
    return g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->bLayerMask;
}
