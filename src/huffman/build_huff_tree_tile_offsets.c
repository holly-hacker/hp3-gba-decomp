#include "types.h"
#include "hw/io_regs.h"
#include "huffman.h"

// Walks count 32-byte tiles of the tree-Huffman stream at pSrc and stores
// each tile's starting ROM bit offset, the bitOffset DecompressHuffTreeTile
// takes. The root node 0x100 is pTree[0]. Unreferenced.
void BuildHuffTreeTileOffsets(const u16 *pSrc, const HuffTreeNode *pTree, u32 *pDest, u32 count)
{
    u32 bits;
    s32 bitsLeft;
    s32 bitsRead;
    u32 startBit;
    u32 bitOffset;
    s32 i;
    u32 node;

    bits = 0;
    startBit = ((const u8 *)pSrc - ROM_BASE) << 3;
    bitOffset = startBit;
    bitsLeft = 0;
    i = 32;
    pTree -= 0x100;
    if (count == 0)
        return;

    bitsRead = 0;
    do
    {
        do
        {
            node = 0x100;
            do
            {
                if (bitsLeft == 0)
                {
                    bitsRead += 16;
                    bits = *pSrc++;
                    bitsLeft = 16;
                }
                node = ((const u16 *)&pTree[node])[bits & 1];
                bits >>= 1;
                bitsLeft--;
            } while (node > 0xFF);
        } while (--i != 0);

        i = 32;
        count--;
        *pDest++ = bitOffset;
        bitOffset = bitsRead - bitsLeft + startBit;
    } while (count != 0);
}
