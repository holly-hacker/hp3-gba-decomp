#include "types.h"
#include "char_block.h"
#include "color.h"
#include "modes.h"
#include "background.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "actor.h"
#include "graphics/oam.h"
#include "overworld/overworld.h"
#include "map.h"

void TickFrameSystems(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        TickOverworldBeforeActors_candidate();

    TickActiveActors();
    TickParticleEmitters();
    TickBgLayers();
    TickScreenWindows_candidate();
    TickPaletteAnimations_candidate();
    TickBgTileAnimations();
    HideUnusedOamEntries();

    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        HandleOverworldPauseMenuInput();
}
