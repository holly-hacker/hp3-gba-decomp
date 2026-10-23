#include "hero.h"
#include "overworld/overworld.h"
#include "world_actors.h"

void HandlePlayerWorldActorCollision(Actor *self, Actor *other)
{
    if (other->wActorType == RoomActorType_WorldActor
        && WORLD_ACTOR_STATE(other)->bBlocksPlayer != 0
        && WORLD_ACTOR_STATE(other)->bBrokenFrame == 0xFF
        && self->bActionState != 0x13)
    {
        StopActorMotion(self);
        SetPartyMemberAnim(self, PartyAnimStand);
        self->bActionFlags &= ~2;
        self->posPrev.x = self->pos.x;
        self->posPrev.y = self->pos.y;
    }
}
