#include "types.h"
#include "font.h"

// Selects font fontId (both descriptor slots) and its colors; see
// TextRenderState. The line height comes from the font's descriptor (JP: the
// two-byte-glyph font's). In 4 bpp mode the color is a 4-bit pixel value.
void SelectTextFont(u32 fontId, u32 color, s32 bgColor)
{
    gTextRenderState.pFont = &g_aFontDescriptors[fontId][0];
    gTextRenderState.pExtFont = &g_aFontDescriptors[fontId][1];
#ifdef VERSION_JP
    gTextRenderState.lineHeight = gTextRenderState.pExtFont->lineHeight;
#else
    gTextRenderState.lineHeight = gTextRenderState.pFont->lineHeight;
#endif
    if (gTextRenderState.is8bpp == 1)
    {
        gTextRenderState.color = color;
        gTextRenderState.tilemapAttr = 0;
    }
    else
    {
        gTextRenderState.color = color & 0xF;
        gTextRenderState.tilemapAttr = 0;
    }
    gTextRenderState.bgColor = bgColor;
}
