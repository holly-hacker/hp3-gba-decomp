#include "types.h"
#include "hw/mem.h"
#include "game/game_modes.h"
#include "graphics/palette.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void InitRoomState(void)
{
    if (g_pRoomObjectStateBuffer == NULL)
        g_pRoomObjectStateBuffer = AllocZeroed(ROOM_OBJECT_STATE_BUFFER_SIZE);
    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
    g_dwColorCycleActiveMask = 0;
    g_bPendingQuestStateOverride_candidate = 0xFF;
    ResetPartyState();
}
