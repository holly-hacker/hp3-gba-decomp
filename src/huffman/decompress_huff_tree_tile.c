#include "types.h"
#include "hw/io_regs.h"
#include "huffman.h"

// Decodes size bytes of a tree-Huffman stream that starts bitOffset bits into
// the ROM, pairing the bytes into halfwords. Bits are read LSB-first from u16s;
// the root node 0x100 starts one halfword into pTree. Unreferenced.
void DecompressHuffTreeTile(u32 bitOffset, u16 *pDest, s32 size, const HuffTreeNode *pTree)
{
    const u16 *pSrc;
    u32 bits;
    s32 bitsLeft;
    u32 pending;
    u32 shift;
    u32 node;
    u16 halfword;

    pTree = (const HuffTreeNode *)((const u16 *)pTree + 1) - 0x100;
    pending = 0x100;
    size >>= 1;
    shift = bitOffset & 0xF;
    bitsLeft = 15 - shift;
    pSrc = (const u16 *)(ROM_BASE + ((bitOffset >> 3) & ~1));
    bits = *pSrc++;
    bits >>= shift;
    while (size > 0)
    {
        node = 0x100;
        do
        {
            node = ((const u16 *)&pTree[node])[bits & 1];
            if (--bitsLeft == -1)
            {
                bits = *pSrc++;
                bitsLeft = 15;
            }
            else
                bits >>= 1;
        } while (node > 0xFF);

        if (pending != 0x100)
        {
            halfword = (node << 8) + pending;
            *pDest++ = halfword;
            size--;
            pending = 0x100;
        }
        else
            pending = node;
    }
}
