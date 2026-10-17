#include "types.h"
#include "overworld/room.h"
#include "scroll.h"

void ClearRoomBgAuxFlag4(void)
{
    g_RoomBgAux.bFlags &= ~4;
}
