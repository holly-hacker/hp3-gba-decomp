#include "types.h"
#include "font.h"

// Draws one line of *ppText if text remains and the line fits in height.
u32 DrawTextLineInHeight(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, const u8 **ppText, u32 align, s32 *pCharBudget)
{
    if (**ppText != 0 && height >= gTextRenderState.lineHeight)
        tileCursor = DrawTextLine(tileCursor, x, y, maxWidth, ppText, align, pCharBudget);
    return tileCursor;
}
