#include "actor.h"

// Allocates a default actor and stamps its type/kind marker.
Actor *AllocActorOfType(s32 type)
{
    Actor *actor = AllocDefaultActor();

    if (actor != NULL) {
        actor->wActorType = type;
        actor->bUnk_0x7C = 5;
    }
    return actor;
}
