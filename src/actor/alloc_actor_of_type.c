#include "actor.h"

// Allocates a default actor and stamps its type/kind marker.
Actor *AllocActorOfType(s32 type)
{
    Actor *actor = AllocDefaultActor();

    if (actor != NULL) {
        actor->wActorType = type;
        actor->bTerrainBlockResponse = TerrainBlockSlide;
    }
    return actor;
}
