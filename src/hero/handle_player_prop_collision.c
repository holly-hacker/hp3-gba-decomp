#include "actor.h"
#include "hero.h"
#include "overworld/overworld.h"

void HandlePlayerPropCollision(Actor *self, Actor *other)
{
    if (other->wActorType == RoomActorType_ScriptedTrigger
        && other->modeState.bPropBlocksPlayer_candidate != 0
        && other->modeState.actor.bRoomActorArg67_candidate == 0xFF
        && self->bActionState != 0x13)
    {
        CancelActorMove_candidate(self);
        SetPartyMemberAnim(self, PartyAnimStand);
        self->bActionFlags &= ~2;
        self->posPrev.x = self->pos.x;
        self->posPrev.y = self->pos.y;
    }
}
