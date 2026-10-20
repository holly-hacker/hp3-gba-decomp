#include "types.h"
#include "background.h"
#include "save.h"
#include "minigame_menu.h"
#include "gen/graphics/minigames/hippogriff.h"

// Draws the four minigame icons, each locked or unlocked.
void DrawMinigameSelectMenu(void)
{
    s32 i;
    u32 unlocked;

    ClearBgTilemap(1);
    LoadBgGraphic(1, gMinigameMenuIcons, 1, 0, 0, 20);

    for (i = 0; i <= 3; i++)
    {
        unlocked = i == 0   ? (g_saveManager.header.bHeaderFlags.all & flWizardCrackerPopItUnlocked) != 0
                   : i == 1 ? (g_saveManager.header.bHeaderFlags.all & flBuckbeakUnlocked) != 0
                   : i == 2 ? (g_saveManager.header.bHeaderFlags.all & flBoggartUnlocked) != 0
                            : (g_saveManager.header.bHeaderFlags.all & flTeaLeafDivinationUnlocked) != 0;
        // The graphic holds the locked icons in rows 20-29 and the unlocked ones in rows 30-39.
        CopyBgScreenRect(1, 4, 10, i * 4, unlocked * 10 + 20, i * 4 + 7, 5);
    }
}
