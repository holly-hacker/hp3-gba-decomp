#include "types.h"
#include "game_modes.h"
#include "display.h"
#include "graphics.h"
#include "object.h"
#include "oam.h"
#include "overworld.h"

void TickFrameSystems(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        TickOverworldBeforeObjects_candidate();

    TickActiveObjects();
    TickParticleEmitters();
    TickBgLayers_candidate();
    TickScreenWindows_candidate();
    TickPaletteAnimations_candidate();
    TickBgTileAnimations_candidate();
    HideUnusedOamEntries();

    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        HandleOverworldPauseMenuInput();
}
