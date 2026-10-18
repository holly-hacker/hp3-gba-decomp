#include "pause_menu.h"
#include "pause_menu_inline.h"
#include "sound.h"

// An immediate row pushes its mode behind a screen transition; any other row fades the menu
// out first (dwModeState 4), and the menu's update pushes the mode when the fade ends.
void SelectListMenuEntry(void)
{
    const ListMenuEntry *pEntry;

    PlaySoundById(1);
    pEntry = &g_ListMenuState.pDefinition->pEntries[g_GameModeStackContext.dwModeScratchB];

    if (pEntry->dwImmediate != 0)
    {
        PlayScreenTransitionOutByIndex(0x3F, 2);
        PushGameMode(pEntry->mode);
    }
    else
    {
        g_GameModeStackContext.dwModeState = 4;
        g_GameModeStackContext.dwModeSubState = 0;
        StartMenuFade();
    }
}
