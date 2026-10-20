#include "types.h"
#include "background.h"
#include "font.h"
#include "modes.h"
#include "default_menu.h"
#include "minigame_menu.h"

void HandleMinigameMenuSelection(u32 index)
{
    ClearBgTilemap(3);
    ClearBgTilemap(2);
    SetTextTargetFromBgControl(g_dwMinigameMenuBg3Control);

    if (IS_MINIGAME_UNLOCKED(index))
    {
        DrawMenuScreenTitle(index + 0xA4A);  // minigame name
        LoadBgGraphic(3, g_apMinigameMenuNumbers[index], 0x60, 0, g_adwMinigameMenuNumberX[index], 5);
    }
    else
    {
        DrawMenuScreenTitle(0xA50);  // "???"
    }

    ShowMinigameLockedMessageIfNeeded(index);
    g_GameModeStackContext.dwCurrentGameModeArg2 = index;
}
