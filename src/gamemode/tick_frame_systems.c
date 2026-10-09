#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "graphics/oam.h"
#include "overworld/overworld.h"

void TickFrameSystems(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        TickOverworldBeforeObjects_candidate();

    TickActiveObjects();
    TickParticleEmitters();
    TickBgLayers_candidate();
    TickScreenWindows_candidate();
    TickPaletteAnimations_candidate();
    TickBgTileAnimations();
    HideUnusedOamEntries();

    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        HandleOverworldPauseMenuInput();
}
