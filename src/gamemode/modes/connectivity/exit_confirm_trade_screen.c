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
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}
