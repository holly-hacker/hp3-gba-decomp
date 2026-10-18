#include "background.h"
#include "cursor.h"
#include "pscreen_information.h"

void ClearHelpScreen(void)
{
    u32 i;

    ClearBgTilemap(2);
    g_HelpState.dwEntryCount = 0;
    g_HelpState.dwTextTileCursor = 0x20;
    if (g_HelpState.pCursor != NULL)
    {
        ReleaseMenuCursor(g_HelpState.pCursor);
        g_HelpState.pCursor = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
    }

    for (i = 0; i < g_HelpState.dwSpriteCount; i++)
        FreeActor(g_HelpState.apSprites[i]);
    g_HelpState.dwSpriteCount = 0;
}
