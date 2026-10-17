#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "color.h"
#include "graphics/display.h"
#include "modes.h"
#include "pscreen_items.h"
#include "mem.h"
#include "actor.h"
#include "cursor.h"
#include "default_menu.h"

void ExitItemsSectionSelect(void)
{
    g_bItemsSectionCursor = g_GameModeStackContext.dwModeScratchB;
    ClearBgTilemap(2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}
