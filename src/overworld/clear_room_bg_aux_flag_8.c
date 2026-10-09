#include "types.h"
#include "overworld/room.h"

void ClearRoomBgAuxFlag8(void)
{
    g_RoomBgAux.bFlags &= ~8;
}
