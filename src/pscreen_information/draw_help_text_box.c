#include "font.h"
#include "text.h"
#include "pscreen_information.h"

void DrawHelpTextBox(s32 x, s32 y, s32 width, s32 height, u32 textId, u32 color)
{
    const u8 *text;

    SelectTextFont(2, color, -1);
    text = GetDialogText(textId);
    g_HelpState.dwTextTileCursor = DrawTextLines(g_HelpState.dwTextTileCursor, x, y, width, height, &text, 0);
}
