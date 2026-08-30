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
