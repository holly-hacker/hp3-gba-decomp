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

extern u8 *gDialogTextBlobBase;
extern u32 *gDialogTextOffsetTable;
extern DialogTextTreeNode *gDialogTextTreeNodes;
extern DialogTextBlob *sDialogTextTable[8];
extern u8 *gDialogTextScratchBuf;
extern u8 gCurrentLanguage;
s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize);
void InitDialogTextEngine(void);
u8 *GetDialogText(s32 stringId);

extern void SetTextTargetFromBgControl_candidate(u32 bgControl);
extern void SelectTextFont_candidate(u32 fontId, u32 color, s32 arg2);
extern u32 DrawTextLines_candidate(u32 tileCursor, s32 x, s32 y, s32 maxWidth, s32 height, u8 **ppText, u32 align);

extern u32 GetLanguage(void);
