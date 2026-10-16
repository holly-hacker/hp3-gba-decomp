#include "types.h"
#include "cursor.h"
#include "default_menu.h"
#include "graphics/display.h"
#include "graphics/graphics.h"

void ExitMenuScreen(void)
{
    if (g_pMenuCursorActor != NULL)
    {
        ReleaseMenuCursor(g_pMenuCursorActor);
        g_pMenuCursorActor = NULL;
    }

    if (g_nMenuScreenPaletteEffectSlot != -1)
    {
        StopPaletteEffect(g_nMenuScreenPaletteEffectSlot);
        g_nMenuScreenPaletteEffectSlot = -1;
    }

    FreeAllParticleEmitters();
    FreeAllParticles();
}
