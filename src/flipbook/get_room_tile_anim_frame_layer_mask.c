#include "types.h"
#include "flipbook.h"

u32 GetRoomTileAnimFrameLayerMask(const RoomTileAnimation *pAnim)
{
    return g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->bLayerMask;
}
