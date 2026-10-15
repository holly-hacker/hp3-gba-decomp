#include "types.h"
#include "font.h"
#include "dialog.h"

// Draws up to charBudget characters of the next line. A line drawn in full moves the
// text down a line; otherwise the line is redrawn from its start next time. Returns
// nonzero once no further line fits.
u32 DrawDialogTextLine(s32 charBudget)
{
    u32 tileCursor;

    tileCursor = DrawTextLineInHeight(g_DialogState_candidate.wTileCursor,
                                      g_DialogState_candidate.bArg18 * 56 + 0x40,
                                      g_DialogState_candidate.bTextY, DIALOG_TEXT_MAX_WIDTH,
                                      g_DialogState_candidate.wTextHeightLeft,
                                      &g_DialogState_candidate.pText,
                                      g_DialogState_candidate.bArg18, &charBudget);
    if (charBudget != 0)
    {
        g_DialogState_candidate.wRevealCount = 0;
        g_DialogState_candidate.bTextY += GetTextLineHeight();
        g_DialogState_candidate.wTextHeightLeft -= GetTextLineHeight();
        g_DialogState_candidate.pLineStart = g_DialogState_candidate.pText;
        g_DialogState_candidate.wTileCursor = tileCursor;
    }
    else
        g_DialogState_candidate.pText = g_DialogState_candidate.pLineStart;

    return g_DialogState_candidate.wTextHeightLeft < GetTextLineHeight();
}
