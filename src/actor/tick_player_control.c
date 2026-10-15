#include "types.h"
#include "input.h"
#include "actor.h"
#include "mem.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

// Action state 0x21, the controlled party leader: walks with the D-pad, B casts the
// selected field spell and L/R change the leader. Does nothing in room 0x20, the
// portrait room passage.
void TickPlayerControl(Actor *actor)
{
    s32 stopped;
    s8 direction;
    u8 facing;

    if (g_bCurrentRoomId == 0x20)  // portrait room passage
        return;

    if (actor->vel.x == 0 && actor->vel.y == 0)
        stopped = 1;
    else
        stopped = 0;
    if (stopped)
        actor->dwFlags &= ~ActorFlagAnimPaused;
    SetActorFlags(actor, ActorFlagTerrainCollisionA_candidate);

    direction = GetDpadDirection();
    if (direction != DirectionNone) {
        facing = ApplyTerrainToWalkVelocity(actor, direction);
        if (stopped == 1 || actor->bFacing != (s8)facing) {
            SetActorActionSubState(actor, 3);
            actor->bFacing = facing;
            SetPartyMemberAnim(actor, PartyAnimWalk);
        }
        if (actor->bTerrainType == 0x2D && stopped)
            g_dwUnk03003234 = 1;
    }
    else if ((actor->bTerrainType != 0x2D || stopped) && actor->bActionSubState != 2) {
        SetActorActionSubState(actor, 2);
        CancelActorMove_candidate(actor);
        SetPartyMemberAnim(actor, PartyAnimStand);
    }

    if ((g_wKeysPressed & KeyB) && g_dwPendingCameraFocusFlag == 0 && actor->wCharacterId_candidate != 4) {
        if (actor->bTerrainType != 0x2D || stopped)
            StartFieldSpellCast(actor);
    }
    else if ((g_wKeysPressed & (KeyL | KeyR)) && g_dwPendingCameraFocusFlag == 0) {
        if (g_wKeysPressed & KeyR)
            CyclePartyLeaderSelection_candidate(actor, 1);
        else
            CyclePartyLeaderSelection_candidate(actor, 0);
    }
}
