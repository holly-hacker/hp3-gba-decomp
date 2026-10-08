#include "types.h"
#include "overworld/room.h"

u32 GetRoomTileAnimFrameDelay(const RoomTileAnimation *pAnim)
{
    return g_apRoomTileAnimSets[pAnim->bSet]->apFrames[pAnim->bStep]->bDelay;
}
