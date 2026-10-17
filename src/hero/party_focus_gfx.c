#include "actor.h"
#include "gen/graphics/overworld.h"
#include "hero.h"

const ActorGfxRecord g_UnusedPartyGfx = {
    (void *)gOverworldPlayer002Tiles, (void *)gOverworldPlayer002Frames,
};
// Replaces the walk sprites of fighter 1 while g_dwPendingCameraFocusFlag is set.
const ActorGfxRecord g_PartyFocusGfx_candidate = {
    (void *)gOverworldPlayer003Tiles, (void *)gOverworldPlayer003Frames,
};
