#include "background.h"
#include "color.h"
#include "modes.h"
#include "actor.h"
#include "pscreen_connectivity.h"
#include "cursor.h"
#include "default_menu.h"

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
