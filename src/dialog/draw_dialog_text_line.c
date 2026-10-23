#include "types.h"
#include "font.h"
#include "dialog.h"

// Draws up to charBudget characters of the next line. A line drawn in full moves the
// text down a line; otherwise the line is redrawn from its start next time. Returns
// nonzero once no further line fits.
u32 DrawDialogTextLine(s32 charBudget)
{
    u32 tileCursor;

    tileCursor = DrawTextLineInHeight(g_DialogState.wTileCursor,
                                      g_DialogState.bTextAlign * 56 + 0x40,
                                      g_DialogState.bTextY, DIALOG_TEXT_MAX_WIDTH,
                                      g_DialogState.wTextHeightLeft,
                                      &g_DialogState.pText,
                                      g_DialogState.bTextAlign, &charBudget);
    if (charBudget != 0)
    {
        g_DialogState.wRevealCount = 0;
        g_DialogState.bTextY += GetTextLineHeight();
        g_DialogState.wTextHeightLeft -= GetTextLineHeight();
        g_DialogState.pLineStart = g_DialogState.pText;
        g_DialogState.wTileCursor = tileCursor;
    }
    else
        g_DialogState.pText = g_DialogState.pLineStart;

    return g_DialogState.wTextHeightLeft < GetTextLineHeight();
}
