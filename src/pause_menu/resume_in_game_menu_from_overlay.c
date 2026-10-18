#include "background.h"
#include "pause_menu.h"

// Restarts the in-game menu at the saved row behind an overlay fade-in. No references to it
// have been found.
void ResumeInGameMenuFromOverlay(void)
{
    ClearBgTilemap(2);
    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwModeScratchB = g_ListMenuState.bInGameMenuCursor;
    StartMenuOverlayFadeIn();
}
