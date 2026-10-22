#include "types.h"
#include "hero.h"
#include "input.h"
#include "map.h"
#include "modes.h"
#include "map_doors.h"

// Collision callback of a portrait door (room actor type 13). Every crossing
// goes through portrait_room_passage (32), which the player walks across on
// their own: down and left from entry 1 when the destination is on a lower
// floor (GetRoomFloorLevel), up and right from entry 0 otherwise. The
// destination room rides along as the mode's third argument, and the
// passage's portrait door at the far end leaves for it with the original
// door's exit param.
void HandlePortraitDoorTouch(Actor *pSelf, Actor *pOther)
{
    if (pOther->wActorType != RoomActorType_Player)
        return;
    if (pOther->bActionSubState == 4)
        return;

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == RoomPortraitRoomPassage)
    {
        g_abRoomScriptExitParams_candidate[0] = g_dwPortraitPassageExitParam;
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, g_GameModeStackContext.dwCurrentGameModeArg3);
        return;
    }

    if (pSelf->modeState.door.bRequireAPress && !(g_wKeysPressed & KeyA))
        return;

    g_dwPortraitPassageExitParam = pSelf->modeState.door.abExitParams[0];
    if (GetRoomFloorLevel(g_bCurrentRoomId)
        > GetRoomFloorLevel(pSelf->scriptState.wDoorDestinationRoom))
        g_abRoomScriptExitParams_candidate[0] = 1;
    else
        g_abRoomScriptExitParams_candidate[0] = 0;
    PushGameMode_3(Overworld, OverworldEntryEnterRoom, RoomPortraitRoomPassage,
                   pSelf->scriptState.wDoorDestinationRoom);
}
