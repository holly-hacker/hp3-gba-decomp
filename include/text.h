#pragma once

#include "types.h"

// See docs/formats/text.md.

typedef enum {
    DialogTextOk       = 0,
    DialogTextNoBlob   = 1, // InitDialogTextTable never called
    DialogTextOverflow = 2, // decoded string would overflow maxSize
} DialogTextResult;

// Huffman tree node, 4 bytes: a child <=0xFF is a decoded output byte
// (leaf), >0xFF is the next node's index.
typedef struct {
    u16 zeroChild;
    u16 oneChild;
} DialogTextTreeNode;

// One language's compressed dialog-text blob (sDialogTextTable[i]):
// [u32 offsetTableOffset][Huffman tree][per-string u32 offset table]
// [compressed bitstreams]. offsetTableOffset is the byte offset from the
// blob base to the offset table, i.e. the tree table's byte length + 4.
typedef struct {
    u32 offsetTableOffset;
    DialogTextTreeNode nodes[1]; // variable-length
} DialogTextBlob;

// Language ids, as stored in gCurrentLanguage and used to index sDialogTextTable.
typedef enum {
    LanguageEnglishUS = 0,
    LanguageEnglishGB = 1,
    LanguageFrench    = 2,
    LanguageGerman    = 3,
    LanguageSpanish   = 4,
    LanguageItalian   = 5,
    LanguageDutch     = 6,
    LanguageDanish    = 7,
} Language;

// Font descriptor, partial. Widths are indexed by (glyphCode - firstCode).
typedef struct {
    u16 unk0;
    u16 firstCode;
    u16 lastCode;
    u16 unk6;
    u32 unk8;
    const u8 *pWidths;
} FontDescriptor;

// Text renderer state at 0x03003110, partial.
typedef struct {
    FontDescriptor *pFont;      // glyph codes <= 0xEF
    FontDescriptor *pExtFont;   // two-byte glyph codes (first byte > 0xEF)
    u8 unk8[9];
    u8 lineHeight;
} TextRenderState;

extern u8 *gDialogTextBlobBase;
extern u32 *gDialogTextOffsetTable;
extern DialogTextTreeNode *gDialogTextTreeNodes;
extern DialogTextBlob *sDialogTextTable[8];
extern u8 *gDialogTextScratchBuf;
extern u8 gCurrentLanguage;
extern u8 gLocaleThousandsSep;
extern TextRenderState gTextRenderState;
extern const u8 *sTextMacroTable[4];
s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize);
void InitDialogTextEngine(void);
u8 *GetDialogText(s32 stringId);

s32 InitDialogTextTable(DialogTextBlob *blob);
extern u32 GetGlyphWidth(FontDescriptor *font, u16 glyphCode);
extern u32 MeasureMacroString(const u8 *pStr);
extern u32 DrawTextLine(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 **ppText, u32 align, s32 *pCharBudget);
extern u32 PrintTextBox(u32 tileCursor, s32 x, s32 y, s32 maxWidth, const u8 *pText, u32 align);
extern u32 DrawStringAligned(u32 tileCursor, s32 x, s32 y, const u8 *pText, u32 align);
extern void SetTextTargetFromBgControl(u32 bgControl);
extern void SelectTextFont(u32 fontId, u32 color, s32 arg2);
extern u32 DrawTextLines(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, u8 **ppText, u32 align);

extern u32 GetLanguage(void);
extern void SetLanguage(u32 languageId);
