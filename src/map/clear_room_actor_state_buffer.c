#include "mem.h"
#include "map.h"

void ClearRoomActorStateBuffer(void)
{
    memset(g_pRoomActorStateBuffer, 0, ROOM_ACTOR_STATE_BUFFER_SIZE);
}
