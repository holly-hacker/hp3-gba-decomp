#include "types.h"
#include "graphics/graphics.h"

// Decodes size bytes; bits are read LSB-first from u16s and the bytes paired into
// halfwords for VRAM.
void DecompressHuffTree(const HuffTreeNode *pTree, void *dst, s32 size)
{
    s32 node = 0;
    s32 i = 0;
    const u16 *pStream;
    s32 bitsLeft;
    s32 bits;
    s32 pending;
    u16 *pOut;

    bits = *(const u16 *)pTree * sizeof(HuffTreeNode);
    pTree++;
    bitsLeft = 0;
    pending = 0x100;
    pStream = (const u16 *)((const u8 *)pTree + bits);
    pOut = dst;
    size >>= 1;

    while (i < size)
    {
        node = 0;
    next:
        if (--bitsLeft == -1)
        {
            bits = *pStream++;
            bitsLeft = 15;
        }
        else
        {
            bits >>= 1;
        }
        node = *(const u16 *)((const u8 *)&pTree[node] + ((bits & 1) << 1));
        if (node > 0xFF)
        {
            node -= 0x100;
            goto next;
        }

        if (pending != 0x100)
        {
            pOut[i] = (node << 8) + pending;
            i++;
            pending = 0x100;
        }
        else
        {
            pending = node;
        }
    }

    if (pending != 0x100)
        ((u8 *)pOut)[i * 2] = node;
}
