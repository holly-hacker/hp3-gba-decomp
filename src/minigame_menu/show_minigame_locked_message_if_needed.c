#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "default_menu.h"
#include "minigame_menu.h"

void ShowMinigameLockedMessageIfNeeded(u32 index)
{
    const u8 *text;

    ClearBgTilemapRect(2, 3, 16, 27, 3);

    if (!IS_MINIGAME_UNLOCKED(index))
    {
        SetTextTargetFromBgControl(g_dwCommonBg2Control);
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x3A7);  // "This game is not yet unlocked."
        DrawTextLines(0xC0, 0x78, 0x84, 0xB4, 0x20, &text, 1);
    }
}
