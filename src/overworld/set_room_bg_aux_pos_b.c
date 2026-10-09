#include "types.h"
#include "overworld/room.h"

void SetRoomBgAuxPosB(const s32 *pos)
{
    g_RoomBgAux.aPosB[0] = pos[0];
    g_RoomBgAux.aPosB[1] = pos[1];
}
