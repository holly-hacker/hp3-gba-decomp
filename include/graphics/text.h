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

extern u8 *gDialogTextBlobBase;
extern u32 *gDialogTextOffsetTable;
extern DialogTextTreeNode *gDialogTextTreeNodes;
extern DialogTextBlob *sDialogTextTable[8];
extern u8 *gDialogTextScratchBuf;
extern u8 gCurrentLanguage;
extern u8 gLocaleThousandsSep;

s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize);
void InitDialogTextEngine(void);
u8 *GetDialogText(s32 stringId);
u8 *FormatDecimal(s32 value, u8 *pBuf);

s32 InitDialogTextTable(DialogTextBlob *blob);

extern u32 GetLanguage(void);
extern void SetLanguage(u32 languageId);
