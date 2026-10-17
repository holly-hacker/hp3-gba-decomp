#include "types.h"
#include "color.h"
#include "mem.h"
#include "game/game_modes.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "hero.h"

void InitRoomState(void)
{
    if (g_pRoomActorStateBuffer == NULL)
        g_pRoomActorStateBuffer = AllocZeroed(ROOM_ACTOR_STATE_BUFFER_SIZE);
    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
    g_dwColorCycleActiveMask = 0;
    g_bPendingQuestStateOverride_candidate = 0xFF;
    ResetPartyState();
}
