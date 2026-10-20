#include "actor.h"
#include "gen/graphics/overworld.h"
#include "npc_actor.h"

// The drop shadow under an overworld actor; see SpawnShadowActor.
const ActorGfxRecord g_ShadowActorGfx = {
    (void *)gActorShadowTiles, (void *)gActorShadowFrames,
};
