#include "types.h"
#include "text.h"

// Decompresses one string from the active language blob's Huffman-style
// bitstream into outBuf. Returns 0 on success, 1 if no language blob is
// installed (InitDialogTextTable never called), 2 if the decoded string
// would overflow maxSize.
s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize)
{
    u8 *cursor;
    u8 curByte;
    u32 bitPos;
    u32 writeIndex;
    u32 pending;
    u32 pendingFlag;
    u16 node;
    u32 nextWriteIndex;

    pending = 0;
    pendingFlag = 0;

    if (gDialogTextBlobBase == 0)
        return DialogTextNoBlob;

    cursor = gDialogTextBlobBase + gDialogTextOffsetTable[stringId];
    writeIndex = 0;
    bitPos = 0;
    curByte = *cursor++;

    do
    {
        node = 0x100;
        nextWriteIndex = writeIndex + 1;
        do
        {
            if ((curByte >> bitPos) & 1)
                node = gDialogTextTreeNodes[node - 0x100].oneChild;
            else
                node = gDialogTextTreeNodes[node - 0x100].zeroChild;

            bitPos++;
            if (bitPos == 8)
            {
                bitPos = 0;
                curByte = *cursor++;
            }
        } while (node > 0xff);

        outBuf[writeIndex] = (u8)node;
        writeIndex = nextWriteIndex;

        // decoded bytes >0xef start a two-byte extended glyph code, paired
        // with the next decoded byte
        if ((u8)node > 0xef && !pendingFlag)
        {
            pending = (u8)node << 8;
            pendingFlag = 1;
        }
        else if (pendingFlag)
        {
            pending |= (u8)node;
            pendingFlag = 0;
        }
        else
        {
            pending = (u8)node;
        }

        if (outBuf[writeIndex - 1] != 0)
        {
            if (writeIndex == maxSize)
                return DialogTextOverflow;
        }
    } while (pending != 0);

    return DialogTextOk;
}
