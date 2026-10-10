#define MEASURE_MACRO_STRING_LINKAGE extern inline
#define GET_TEXT_HEIGHT_LINKAGE extern inline
#include "types.h"
#include "font.h"

// Draws pText with (x, y) as the anchor given by align: 1 centers it on x,
// 2 ends it at x, 4 centers it on y and 8 ends it at y; other values draw
// from (x, y). Returns the tile cursor from DrawString.
u32 DrawStringAligned(u32 tileCursor, s32 x, s32 y, const u8 *pText, u32 align)
{
    s32 width;
    s32 height;
    s32 drawX;
    s32 drawY;

    drawX = x;
    drawY = y;

    if (align == 1)
    {
        width = MeasureMacroString(pText);
        drawX -= (width + 1) / 2;
    }
    else if (align == 2)
    {
        width = MeasureMacroString(pText);
        drawX -= width;
    }

    if (align == 4)
    {
        height = GetTextHeight(pText);
        drawY -= (height + 1) / 2;
    }
    else if (align == 8)
    {
        height = GetTextHeight(pText);
        drawY -= height;
    }

    return DrawString(tileCursor, drawX, drawY, pText);
}
