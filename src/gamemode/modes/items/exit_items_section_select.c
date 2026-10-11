#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "menu/items_menu.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

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
