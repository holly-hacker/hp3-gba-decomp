#include "font.h"
#include "dialog.h"
#include "dialog_box.h"

void DrawDialogTextPage(void)
{
    DrawTextLines(g_DialogState.wTileCursor, g_DialogState.bTextAlign * 56 + 0x40,
                  g_DialogState.bTextY, DIALOG_TEXT_MAX_WIDTH,
                  g_DialogState.wTextHeightLeft, &g_DialogState.pText,
                  g_DialogState.bTextAlign);
    g_DialogState.pLineStart = g_DialogState.pText;
}
