#include "types.h"
#include "flipbook.h"

u32 GetRoomTileAnimFrameDelay(const RoomTileAnimation *pAnim)
{
    return g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->bDelay;
}
