#include "types.h"
#include "font.h"

// Draws lines of *ppText from (x, y) while text remains and another line fits
// in height. Leaves *ppText at the first undrawn line.
u32 DrawTextLines(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, u8 **ppText, u32 align)
{
    s32 charBudget;

    charBudget = 0x7FFFFFFF;
    while (**ppText != 0 && height >= gTextRenderState.lineHeight)
    {
        tileCursor = DrawTextLine(tileCursor, x, y, maxWidth, (const u8 **)ppText, align, &charBudget);
        y += gTextRenderState.lineHeight;
        height -= gTextRenderState.lineHeight;
    }
    return tileCursor;
}
