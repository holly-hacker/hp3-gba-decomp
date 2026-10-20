#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pouring_minigame.h"

void DrawServePumpkinJuiceScore(void)
{
    const u8 *text;

    SelectTextFont(6, 0, -1);
    SetTextMacro1Number(g_ServePumpkinJuice.dwScore);
    text = GetDialogText(0xA5D);  // "Score: @1"
    FillBgTilemapRect(3, 0, 0, 16, 2, 0);
    g_ServePumpkinJuice.dwMenuTileBase = g_ServePumpkinJuice.dwTileCursor =
        DrawStringAligned(g_ServePumpkinJuice.dwTextTileBase, 0x32, 0, text, 1);
    g_ServePumpkinJuice.dwScoreChanged = 0;
}
