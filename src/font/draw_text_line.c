#define MEASURE_MACRO_STRING_LINKAGE extern inline
#include "types.h"
#include "font.h"

#ifdef VERSION_JP
// JP only. Looks up the flag bits of a two-byte glyph in FontDescriptor.pGlyphFlags: a
// table with 2 bits per glyph, 16 glyphs per 32-bit word, indexed by (code - firstCode).
// DrawTextLine uses bit 1 to drop its pending line-break point and bit 0 to record one.
// What the bits mean in game terms is unconfirmed.
static inline u32 GlyphFlagSet(FontDescriptor *font, u16 code, u32 flag)
{
    u16 glyphIndex = code - font->firstCode;
    u32 wordIndex = glyphIndex >> 4;
    u32 slot = glyphIndex & 0xF;
    u32 flags = font->pGlyphFlags[wordIndex] >> (slot * 2);

    return flags & flag;
}

// JP copies the lead byte of a two-byte glyph along with its second byte.
#define COPIES_NEXT_BYTE(c) ((c) == 0x40 || (c) > 0xEF)
#else
#define COPIES_NEXT_BYTE(c) ((c) == 0x40)
#endif

// Draws one line of *ppText and leaves *ppText at the start of the next line.
// The line ends at the last wrap point (a space, or 0xF0 0x00 in US), at a newline, or
// after a hyphen when nothing else fits within maxWidth. A 0x40 prefix selects a macro
// string from sTextMacroTable (code - 0x31); codes above 0xEF are the first byte of a
// two-byte glyph code. *pCharBudget limits how many glyph codes are drawn.
// Returns the tile cursor from DrawStringAligned.
u32 DrawTextLine(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 **ppText, u32 align, s32 *pCharBudget)
{
    u8 lineBuf[0x40];
    const u8 *pCode;
    const u8 *pWrap;
    const u8 *pHyphenWrap;
    u8 *pOut;
    s32 width;
    u16 code;
    FontDescriptor *font;
#ifdef VERSION_JP
    u8 lead;
    const u8 *pHeldBreak;
#endif

    pCode = *ppText;
    pWrap = 0;
    pHyphenWrap = 0;
#ifdef VERSION_JP
    pHeldBreak = 0;
#endif
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
            width += MeasureMacroString(sTextMacroTable[*pCode - 0x31]);
#ifdef VERSION_JP
            if (width >= maxWidth - 8)
            {
                pCode--;
                pWrap = pCode;
                break;
            }
#endif
        }
#ifdef VERSION_JP
        else if (*pCode > 0xEF)
        {
            code = (pCode[0] << 8) | pCode[1];
            if (code == 0xF000)
                pWrap = pCode;

            font = gTextRenderState.pExtFont;
            width += GetGlyphWidth(font, code);

            if (GlyphFlagSet(font, code, 2))
                pHeldBreak = 0;
            else if (GlyphFlagSet(font, code, 1))
            {
                if (pHeldBreak == 0)
                {
                    pWrap = pCode;
                    pHeldBreak = pCode;
                }
            }
            else if (pHeldBreak == 0)
                pWrap = pCode;
            else
                pHeldBreak = 0;
            pCode++;
        }
        else
        {
            code = *pCode;
            if (code == ' ')
                pWrap = pCode;

            font = gTextRenderState.pFont;
            width += GetGlyphWidth(font, code);

            if (width <= maxWidth && code == '-')
                pHyphenWrap = pCode + 1;
        }
#else
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
#endif
        pCode++;
    }

    if (*pCode == 0 && width <= maxWidth)
        pWrap = pCode;

#ifdef VERSION_JP
    // Copying the byte into a local exists only to make the register allocation match.
    lead = pWrap[0];
    if (lead == 0xF0 && pWrap[1] == 0)
        pWrap += 2;
#endif

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
                if (COPIES_NEXT_BYTE(*pCode))
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
