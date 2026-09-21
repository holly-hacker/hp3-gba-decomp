#include "types.h"
#include "text.h"

// Draws one line of *ppText and leaves *ppText at the start of the next line.
// The line ends at the last space (or 0xF0 0x00), at a newline, or after a hyphen
// when nothing else fits within maxWidth. A 0x40 prefix selects a macro string
// from sTextMacroTable (code - 0x31); codes above 0xEF are the first byte of a
// two-byte glyph code. *pCharBudget limits how many glyph codes are drawn.
// Returns the tile cursor from DrawStringAligned.
u32 DrawTextLine(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 **ppText, u32 align, s32 *pCharBudget)
{
    u8 lineBuf[0x40];
    const u8 *pCode;
    const u8 *pWrap;
    const u8 *pHyphenWrap;
    const u8 *pMacro;
    u8 *pOut;
    s32 width;
    s32 macroWidth;
    u32 macroCode;
    u16 code;
    FontDescriptor *font;

    pCode = *ppText;
    pWrap = 0;
    pHyphenWrap = 0;
    width = 0;

    while (*pCode != 0 && width <= maxWidth)
    {
        if (*pCode == '\n')
        {
            pWrap = pCode;
            break;
        }

        if (*pCode == 0x40)
        {
            pCode++;
            pMacro = sTextMacroTable[*pCode - 0x31];
            macroWidth = 0;
            while (*pMacro != 0)
            {
                if (*pMacro == 0x40)
                {
                    pMacro++;
                    macroWidth += MeasureMacroString(sTextMacroTable[*pMacro - 0x31]);
                }
                else
                {
                    macroCode = *pMacro;
                    if (macroCode > 0xEF)
                    {
                        macroCode <<= 8;
                        pMacro++;
                        macroCode |= *pMacro;
                        font = gTextRenderState.pExtFont;
                    }
                    else
                        font = gTextRenderState.pFont;
                    macroWidth += GetGlyphWidth(font, macroCode);
                }
                pMacro++;
            }
            width += macroWidth;
        }
        else
        {
            if (*pCode == ' ' || (*pCode == 0xF0 && pCode[1] == 0))
                pWrap = pCode;

            code = *pCode;
            if ((u8)code > 0xEF)
            {
                code <<= 8;
                pCode++;
                code |= *pCode;
                font = gTextRenderState.pExtFont;
            }
            else
                font = gTextRenderState.pFont;
            width += GetGlyphWidth(font, code);

            if (*pCode == '-' && width <= maxWidth)
                pHyphenWrap = pCode + 1;
        }
        pCode++;
    }

    if (*pCode == 0 && width <= maxWidth)
        pWrap = pCode;

    if (pWrap != 0 || pHyphenWrap != 0)
    {
        if (pWrap == 0)
            pWrap = pHyphenWrap;

        pOut = lineBuf;
        pCode = *ppText;
        if (pCode != pWrap && *pCharBudget != 0)
        {
            do
            {
                if (*pCode == 0x40)
                    *pOut++ = *pCode++;
                *pOut++ = *pCode++;
                (*pCharBudget)--;
            } while (pCode != pWrap && *pCharBudget != 0);
        }
        *pOut = 0;
        *ppText = pCode;

        tileCursor = DrawStringAligned(tileCursor, x, y, lineBuf, align);

        if (**ppText == '\n')
            (*ppText)++;
        while (**ppText == ' ')
            (*ppText)++;
    }

    return tileCursor;
}
