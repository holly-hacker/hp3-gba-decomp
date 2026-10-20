#include "types.h"
#include "font.h"
#include "text.h"
#include "pouring_minigame.h"

void DrawServePumpkinJuicePauseMenu(void)
{
    u32 tileCursor = g_ServePumpkinJuice.dwMenuTileBase;
    s32 row;

    for (row = 0; row < 3; row++)
    {
        if (row == g_ServePumpkinJuice.dwMenuSelection)
            SelectTextFont(6, 2, -1);
        else
            SelectTextFont(6, 0, -1);

        // 0xA58 "Resume Game", 0xA59 "Replay", 0xA5A "Exit Game"
        tileCursor = DrawStringAligned(tileCursor, 0x78, 0x40 + row * 16, GetDialogText(row + 0xA58), 1);
    }

    g_ServePumpkinJuice.dwTileCursor = tileCursor;
}
