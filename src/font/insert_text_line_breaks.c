#include "types.h"
#include "font.h"

// Word-wraps pText in place to maxWidth pixels. When the running width reaches
// maxWidth, the last space (or two-byte space 0xF0 0x00) becomes a newline; with
// no space after the last hyphen, a newline is inserted after the hyphen
// instead. Scanning resumes two bytes past the break. JP leaves the text as is.
void InsertTextLineBreaks(u8 *pText, u32 maxWidth)
{
#ifndef VERSION_JP
    u8 *pSpace;
    u8 *pHyphen;
    u8 *pEnd;
    u32 width;
    u32 code;
    FontDescriptor *font;

    pSpace = 0;
    pHyphen = 0;
    width = 0;
    while (*pText != 0)
    {
        code = *pText;
        if (code > 0xEF)
        {
            code <<= 8;
            pText++;
            code |= *pText;
            font = gTextRenderState.pExtFont;
        }
        else
            font = gTextRenderState.pFont;

        if (code == ' ' || ((code >> 8) > 0xEF && (code & 0xFF) == 0))
            pSpace = pText;
        else if (code == '-')
            pHyphen = pText;

        width += GetGlyphWidth(font, code);
        if (width >= maxWidth)
        {
            if (pSpace > pHyphen)
            {
                *pSpace = '\n';
                pText = pSpace + 1;
            }
            else
            {
                if (pHyphen[1] != ' ')
                {
                    for (pEnd = pHyphen; *pEnd != 0; pEnd++)
                        ;
                    for (; pEnd > pHyphen; pEnd--)
                        pEnd[1] = *pEnd;
                }
                pHyphen[1] = '\n';
                pText = pHyphen + 2;
            }
            pSpace = 0;
            pHyphen = 0;
            width = 0;
        }
        pText++;
    }
#endif
}
