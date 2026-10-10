#pragma once

#include "types.h"

// Variable-width text renderer; see docs/formats/fonts.md.

// Font descriptor, filled from a font blob by LoadFontDescriptor (see
// docs/formats/fonts.md). Widths are indexed by (glyphCode - firstCode).
typedef struct {
    u8 height;
    u16 firstCode;
    u16 lastCode;
    u8 lineHeight;              // from g_aFontTable; SelectTextFont applies it
    const u16 *pGlyphOffsets;
    const u8 *pWidths;
#ifdef VERSION_JP
    const u32 *pGlyphFlags;     // 2 flag bits per glyph (see DrawTextLine)
#endif
    const u8 *pBitmaps;
} FontDescriptor;

// Text renderer state (gTextRenderState). DrawString renders one 8-pixel-wide
// column of tiles at a time into a RAM buffer, then copies it to pTiles and
// points the tilemap entries at it.
typedef struct {
    FontDescriptor *pFont;      // 0x00, glyph codes <= 0xEF
    FontDescriptor *pExtFont;   // 0x04, two-byte glyph codes (first byte > 0xEF)
    u32 color;                  // 0x08, added to each 2-bit glyph pixel value
    s32 bgColor;                // 0x0C, pixel value of the cell background;
                                //       -1 draws over the tiles already mapped
    u8 tilemapAttr;             // 0x10, ORed into written tilemap entries
    u8 lineHeight;              // 0x11
    u16 *pTilemap;              // 0x14, BG screen base
    u16 *pTilemapBase;          // 0x18, set with pTilemap; not read by the renderer
    u8 *pTiles;                 // 0x1C, BG character base
    u16 tileSize;               // 0x20, bytes per tile: 0x20 (4 bpp) or 0x40 (8 bpp)
    u32 is8bpp;                 // 0x24
} TextRenderState;

// ROM font lists: blob pointer and the line height copied to the descriptor.
// g_aFontTable holds the Latin fonts; JP adds g_aExtFontTable, the
// two-byte-glyph (kana/kanji) fonts for descriptor slot 1.
typedef struct {
    const u8 *pBlob;
    u32 lineHeight;
} FontTableEntry;

extern const FontTableEntry g_aFontTable[12];
#ifdef VERSION_JP
extern const FontTableEntry g_aExtFontTable[12];
#endif
// Descriptor pairs, one per font index (slot 0 and slot 1).
extern FontDescriptor g_aFontDescriptors[12][2];
extern TextRenderState gTextRenderState;
// Target fields (pTilemap..is8bpp) saved by SaveTextTarget.
extern TextRenderState gSavedTextTarget;
// Macro strings that 0x40-prefixed codes 0x31-0x34 expand to.
extern u8 *sTextMacroTable[4];

void InsertTextLineBreaks(u8 *pText, u32 maxWidth);
u32 DrawTextLine(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 **ppText, u32 align, s32 *pCharBudget);
u32 DrawStringAligned(u32 tileCursor, s32 x, s32 y, const u8 *pText, u32 align);
u32 DrawString(u32 tileCursor, s32 x, s32 y, const u8 *pText);
void LoadFontDescriptor(u32 index, u32 slot);
void FlipTileHorizontally(u8 *pTile);
void InitTextMacroTable(void);
void SetTextTargetFromBgControl(u32 bgControl);
void SetTextTarget(u16 *pTilemap, u8 *pTiles, u32 is8bpp);
void SaveTextTarget(void);
void RestoreTextTarget(void);
void SelectTextFont(u32 fontId, u32 color, s32 bgColor);
void SetTextLineHeight(u32 lineHeight);
u32 MeasureMacroString(const u8 *pStr);
u32 GetTextHeight(const u8 *pStr);
u8 *ExpandTextMacros(u8 *pDest, const u8 *pSrc, s32 maxLen);
u32 DrawTextLines(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, u8 **ppText, u32 align);
u32 DrawTextLineInHeight(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, const u8 **ppText, u32 align, s32 *pCharBudget);
u32 PrintTextBox(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 *pText, u32 align);
void FillTilemapRow(s32 left, s32 row, s32 right, u16 entry);
void ClearTilemapRow(s32 left, s32 row, s32 right);

// Fill text macro @N (sTextMacroTable slot N - 1) with a string or a signed
// decimal number.
void SetTextMacroString(const u8 *pString, u32 slot);
void SetTextMacro1String(const u8 *pString);
void SetTextMacro2String(const u8 *pString);
void SetTextMacro3String(const u8 *pString);
void SetTextMacroNumber(s32 value, u32 slot);
void SetTextMacro1Number(s32 value);
void SetTextMacro2Number(s32 value);
void SetTextMacro3Number(s32 value);
void SetTextMacro4String(const u8 *pString);

u32 GetTextLineHeight(void);
void FillTextTileColumn(u32 *pBuf, u32 tileCount, u32 color);
void ReadTextTileColumn(u32 *pBuf, u32 tileCount, u16 *pEntry, u8 *pTiles);
void WriteTextTileColumn(u32 *pBuf, u32 tileCount, u16 *pEntry, u8 *pTiles, u32 tileIndex);
u16 *GetTilemapEntryAt(u16 *pTilemap, s32 x, s32 y);
u32 GetGlyphWidth(FontDescriptor *font, u16 glyphCode);

// The ROM inlines MeasureMacroString and GetTextHeight into the renderer
// functions that follow them, as one translation unit with inline definitions
// would, while code elsewhere calls them out of line. A file that defines
// MEASURE_MACRO_STRING_LINKAGE or GET_TEXT_HEIGHT_LINKAGE before including this
// header sees the definition: `extern inline` in the inlining callers, empty in
// the file that emits the out-of-line copy. Other files see only the prototype.

#ifdef MEASURE_MACRO_STRING_LINKAGE
// Returns the pixel width of a glyph string. A 0x40 prefix selects a macro
// string from sTextMacroTable (code - 0x31), which is measured recursively.
MEASURE_MACRO_STRING_LINKAGE u32 MeasureMacroString(const u8 *pStr)
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
#endif

#ifdef GET_TEXT_HEIGHT_LINKAGE
// Returns the pixel height of a drawn string: 0 when empty, otherwise the
// font height (JP: the taller of the two selected fonts).
GET_TEXT_HEIGHT_LINKAGE u32 GetTextHeight(const u8 *pStr)
{
    u32 height;

    height = 0;
    if (*pStr != 0)
    {
#ifdef VERSION_JP
        if (gTextRenderState.pExtFont->height > gTextRenderState.pFont->height)
            height = gTextRenderState.pExtFont->height;
        else
            height = gTextRenderState.pFont->height;
#else
        height = gTextRenderState.pFont->height;
#endif
    }
    return height;
}
#endif
