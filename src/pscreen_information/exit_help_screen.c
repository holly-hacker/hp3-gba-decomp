#include "types.h"
#include "color.h"
#include "particles.h"
#include "pscreen_information.h"
#include "cursor.h"

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
