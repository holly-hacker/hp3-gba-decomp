#include "actor.h"
#include "gen/graphics/overworld.h"
#include "timeturner_cutscene.h"

// The drop shadow under each cutscene actor; see SpawnHarryHermionePortInTimeActor.
const ActorGfxRecord g_HarryHermionePortInTimeShadowGfx = {
    (void *)gActorShadowTiles, (void *)gActorShadowFrames,
};
