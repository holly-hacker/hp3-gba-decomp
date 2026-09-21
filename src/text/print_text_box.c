#include "types.h"
#include "text.h"

// Draws pText starting at (x, y), wrapping at maxWidth, one line per call to
// DrawTextLine until the text is exhausted. Returns the last tile cursor.
u32 PrintTextBox(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 *pText, u32 align)
{
    s32 charBudget;

    charBudget = 0x7FFFFFFF;
    while (*pText != 0)
    {
        tileCursor = DrawTextLine(tileCursor, x, y, maxWidth, &pText, align, &charBudget);
        y += gTextRenderState.lineHeight;
    }
    return tileCursor;
}
