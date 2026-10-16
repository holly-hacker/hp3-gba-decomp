#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "color.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "cursor.h"
#include "default_menu.h"

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
