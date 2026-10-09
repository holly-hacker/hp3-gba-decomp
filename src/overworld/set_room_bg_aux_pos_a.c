#include "types.h"
#include "overworld/room.h"

void SetRoomBgAuxPosA(const s32 *pos)
{
    g_RoomBgAux.aPosA[0] = pos[0];
    g_RoomBgAux.aPosA[1] = pos[1];
}
