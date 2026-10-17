#include "background.h"
#include "color.h"
#include "actor.h"
#include "cursor.h"
#include "default_menu.h"
#include "pscreen_connectivity.h"

void ExitConfirmTradeScreen(void)
{
    ClearBgTilemap(2);
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}
