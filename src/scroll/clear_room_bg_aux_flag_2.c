#include "types.h"
#include "overworld/room.h"
#include "scroll.h"

void ClearRoomBgAuxFlag2(void)
{
    g_RoomBgAux.bFlags &= ~2;
}
