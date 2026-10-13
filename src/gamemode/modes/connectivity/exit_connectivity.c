#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/connectivity.h"
#include "menu/main_menu.h"

void ExitConnectivity(void)
{
    g_bConnectivityMenuCursor = g_GameModeStackContext.dwModeScratchB;
    ClearBgTilemap(2);
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}
