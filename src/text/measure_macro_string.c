#include "types.h"
#include "text.h"

// Returns the pixel width of a glyph string. A 0x40 prefix selects a macro
// string from sTextMacroTable (code - 0x31), which is measured recursively.
u32 MeasureMacroString(const u8 *pStr)
{
    u32 width;
    u32 code;
    FontDescriptor *font;

    width = 0;
    while (*pStr != 0)
    {
        if (*pStr == 0x40)
        {
            pStr++;
            width += MeasureMacroString(sTextMacroTable[*pStr - 0x31]);
        }
        else
        {
            code = *pStr;
            if (code > 0xEF)
            {
                code <<= 8;
                pStr++;
                code |= *pStr;
                font = gTextRenderState.pExtFont;
            }
            else
                font = gTextRenderState.pFont;
            width += GetGlyphWidth(font, code);
        }
        pStr++;
    }
    return width;
}
