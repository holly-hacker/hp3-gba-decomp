#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "hw/mem.h"
#include "menu/main_menu.h"

void ExitConfirmTradeScreen(void)
{
    ClearBgTilemap(2);
    ReleaseMenuCursor(g_pMenuCursorObject);
    g_pMenuCursorObject = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}
