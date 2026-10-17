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

s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize);

s32 InitDialogTextTable(DialogTextBlob *blob);

// DecompressHuffTree's input: a u16 node count padded to 4 bytes, the nodes, then the
// bitstream. A child below 0x100 is a leaf byte; otherwise it is 0x100 + node index.
typedef struct HuffTreeNode {
    u16 awChildren[2];  // indexed by the next bit
} HuffTreeNode;
extern void DecompressHuffTree(const HuffTreeNode *pTree, void *dst, s32 size);

// Copies DecompressBgTile to IWRAM; see docs/formats/graphics.md
// ("On-demand per-tile BG streaming").
void InstallBgTileCodec(void);
