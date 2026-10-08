#include "types.h"
#include "graphics/object.h"
#include "gen/graphics/overworld.h"
#include "overworld/overworld.h"

const ObjectGfxRecord g_UnusedPartyGfx = {
    (void *)gOverworldPlayer002Tiles, (void *)gOverworldPlayer002Frames,
};
// Replaces the walk sprites of fighter 1 while g_dwPendingCameraFocusFlag is set.
const ObjectGfxRecord g_PartyFocusGfx_candidate = {
    (void *)gOverworldPlayer003Tiles, (void *)gOverworldPlayer003Frames,
};
