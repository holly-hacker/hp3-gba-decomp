#include "types.h"
#include "font.h"

// Draws pText with its top-left at pixel (x, y) of the text target, starting
// at tile tileCursor. Glyphs are rendered one 8-pixel column of tiles at a
// time; each finished column is written to the next tileCount tiles and mapped
// at the next tilemap column. A 0x40 prefix draws a macro string from
// sTextMacroTable (code - 0x31); codes above 0xEF are the first byte of a
// two-byte glyph code. Returns the tile cursor after the last tile used.
u32 DrawString(u32 tileCursor, s32 x, s32 y, const u8 *pText)
{
    u32 column[0x40];   // one column of up to 8 4 bpp (4 8 bpp) tiles
    const u8 *pChar;
    const u8 *pResume;
    u32 inMacro;
    u16 *pEntry;
    u8 *pTiles;
    u32 color;
    FontDescriptor *extFont;
    FontDescriptor *latinFont;
    u32 *pColumn;
    u32 tileCount;
    u32 nextTile;
    FontDescriptor *font;
    u32 code;
    s32 index;
    const u8 *pBits;
    u32 bit;
    u32 cols;
    u32 rows;
    u8 *pDest;
    u32 value;

    nextTile = tileCursor;
    pEntry = GetTilemapEntryAt(gTextRenderState.pTilemap, x, y);
    pTiles = gTextRenderState.pTiles;
    color = gTextRenderState.color;
    font = gTextRenderState.pFont;
    extFont = gTextRenderState.pExtFont;
    latinFont = font;
    x &= 7;
    y &= 7;
#ifdef VERSION_JP
    // Tall enough for the taller of the two fonts.
    if (extFont->height > font->height)
        tileCount = (y + extFont->height + 7) >> 3;
    else
        tileCount = (y + font->height + 7) >> 3;
#else
    tileCount = (y + font->height + 7) >> 3;
#endif
    pColumn = column;
    if (gTextRenderState.bgColor == -1)
        ReadTextTileColumn(column, tileCount, pEntry, pTiles);
    else
        FillTextTileColumn(column, tileCount, gTextRenderState.bgColor);

    pChar = pText;
    pResume = pChar;
    inMacro = 0;
    while (*pChar != 0 || inMacro)
    {
        if (inMacro && *pChar == 0)
        {
            pChar = pResume;
            inMacro = 0;
            if (*pChar == 0)
                break;
        }

        if (!inMacro && *pChar == 0x40)
        {
            pChar++;
            pResume = pChar;
            pChar = sTextMacroTable[*pChar - 0x31];
            pResume++;
            inMacro = 1;
        }

        if (*pChar > 0xEF)
        {
            code = *pChar << 8;
            pChar++;
            code |= *pChar;
            font = extFont;
            index = code - font->firstCode;
        }
        else
        {
            font = latinFont;
            index = *pChar - font->firstCode;
        }
        if (index < 0 || index > font->lastCode - font->firstCode)
            index = 1;

        pBits = font->pBitmaps + font->pGlyphOffsets[index];
        bit = 0;
        cols = font->pWidths[index];
        while (cols--)
        {
            if (gTextRenderState.is8bpp == 1)
            {
                pDest = (u8 *)column + y * 8 + x;
                rows = font->height;
                while (rows--)
                {
                    if (bit == 8)
                    {
                        bit = 0;
                        pBits++;
                    }
                    value = (*pBits >> bit) & 3;
                    if (value != 0)
                        *pDest = value + color;
                    pDest += 8;
                    bit += 2;
                }
            }
            else
            {
                pDest = (u8 *)column + (y * 8 + x) / 2;
                rows = font->height;
                while (rows--)
                {
                    if (bit == 8)
                    {
                        bit = 0;
                        pBits++;
                    }
                    value = (*pBits >> bit) & 3;
                    if (value != 0)
                    {
                        if (!(x & 1))
                        {
                            value = (*pDest & 0xF0) | (value + color);
                            *pDest = value;
                        }
                        else
                            *pDest = (*pDest & 0x0F) | ((value + color) << 4);
                    }
                    pDest += 4;
                    bit += 2;
                }
            }

            x++;
            if (x == 8)
            {
                x = 0;
                WriteTextTileColumn(pColumn, tileCount, pEntry, pTiles, nextTile);
                nextTile += tileCount;
                pEntry++;
                if (gTextRenderState.bgColor == -1)
                    ReadTextTileColumn(pColumn, tileCount, pEntry, pTiles);
                else
                    FillTextTileColumn(pColumn, tileCount, gTextRenderState.bgColor);
            }
        }
        pChar++;
    }

    if (x > 0)
    {
        WriteTextTileColumn(pColumn, tileCount, pEntry, pTiles, nextTile);
        nextTile += tileCount;
    }
    return nextTile;
}
