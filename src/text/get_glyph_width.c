#include "types.h"
#include "text.h"

// Returns the pixel width of glyphCode in font; codes outside the font's range
// use the width stored for glyph index 1, and code 0 has no width.
u32 GetGlyphWidth(FontDescriptor *font, u16 glyphCode)
{
    u32 width;
    s32 index;

    width = 0;
    if (glyphCode != 0)
    {
        index = glyphCode - font->firstCode;
        if (index >= 0 && index <= font->lastCode - font->firstCode)
            width = font->pWidths[index];
        else
            width = font->pWidths[1];
    }
    return width;
}
