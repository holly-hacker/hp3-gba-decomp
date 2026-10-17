#include "font.h"
#include "dialog.h"
#include "dialog_box.h"

void DrawDialogTextPage(void)
{
    DrawTextLines(g_DialogState_candidate.wTileCursor, g_DialogState_candidate.bTextAlign * 56 + 0x40,
                  g_DialogState_candidate.bTextY, DIALOG_TEXT_MAX_WIDTH,
                  g_DialogState_candidate.wTextHeightLeft, &g_DialogState_candidate.pText,
                  g_DialogState_candidate.bTextAlign);
    g_DialogState_candidate.pLineStart = g_DialogState_candidate.pText;
}
