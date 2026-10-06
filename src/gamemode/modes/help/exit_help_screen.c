#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "menu/help.h"
#include "menu/main_menu.h"

void ExitHelpScreen(void)
{
    if (g_HelpState.pCursor != NULL)
    {
        ReleaseMenuCursor(g_HelpState.pCursor);
        g_HelpState.pCursor = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
    }

    if (g_HelpState.dwPaletteEffect != -1)
    {
        StopPaletteEffect(g_HelpState.dwPaletteEffect);
        g_HelpState.dwPaletteEffect = -1;
    }
}
