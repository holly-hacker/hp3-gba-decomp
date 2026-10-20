#include "actor.h"
#include "gen/graphics/overworld.h"
#include "hero.h"

const ActorGfxRecord g_UnusedPartyGfx = {
    (void *)gOverworldPlayer002Tiles, (void *)gOverworldPlayer002Frames,
};
// The walk sprites of a party member casting Lumos (bFighterIndex 1) while its light is lit.
const ActorGfxRecord g_PartyLumosGfx = {
    (void *)gHarryLumosTiles, (void *)gHarryLumosFrames,
};
