#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "input.h"
#include "map.h"
#include "modes.h"
#include "overworld/room.h"
#include "overworld/room_actor.h"
#include "collision.h"

// Collision callback of a door (room actor type 2): the player leaves for the
// destination room through game mode 8, or the door's chain runs instead.
void HandleDoorTouch(Actor *pSelf, Actor *pOther)
{
    u32 i;
    u32 j;
    u8 exitParam;

    if (pSelf->modeState.door.bRequireAPress && !(g_wKeysPressed & KeyA))
        return;
    if (pOther->wActorType != RoomActorType_Player)
        return;
    if (pOther->bActionSubState == 4)
        return;
    if (IsGameModeTransitionPending())
        return;

    for (i = 0; i < 2; i++)
        g_abRoomScriptExitParams_candidate[i] = pSelf->modeState.door.abExitParams[i];

    if (pSelf->modeState.door.bChain)
    {
        RespawnGroupAndRunChain(0, pSelf->modeState.door.bChain);
        return;
    }

    // Grand staircase (30): a door to the second (19) or fourth floor (21)
    // leads to whichever the room switch state selects. Its exit params are
    // rewritten to match, for the next touch.
    if (g_bCurrentRoomId == 30
        && (pSelf->scriptState.wDoorDestinationRoom == 19
            || pSelf->scriptState.wDoorDestinationRoom == 21))
    {
        if (GetRoomSwitchState())
        {
            pSelf->scriptState.wDoorDestinationRoom = 21;
            exitParam = 2;
        }
        else
        {
            pSelf->scriptState.wDoorDestinationRoom = 19;
            exitParam = 1;
        }
        for (j = 0; j < 2; j++)
            pSelf->modeState.door.abExitParams[j] = exitParam;
    }

    PushGameMode_2(Overworld, OverworldEntryEnterRoom, pSelf->scriptState.wDoorDestinationRoom);
}
