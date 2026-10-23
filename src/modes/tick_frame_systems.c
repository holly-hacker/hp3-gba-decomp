#include "char_block.h"
#include "color.h"
#include "modes.h"
#include "background.h"
#include "particles.h"
#include "actor.h"
#include "oam.h"
#include "map.h"
#include "windows.h"

void TickFrameSystems(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        TickOverworldView();

    TickActiveActors();
    TickParticleEmitters();
    TickBgLayers();
    TickScreenWindows();
    TickPaletteAnimations();
    TickBgTileAnimations();
    HideUnusedOamEntries();

    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        HandleOverworldPauseMenuInput();
}
