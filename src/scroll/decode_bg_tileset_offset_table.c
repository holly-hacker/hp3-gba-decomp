#include "types.h"
#include "hw/io_regs.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Builds pTileset from the tileset resource: allocates and fills the per-tile ROM bit offsets
// from the compressed length table, and copies the Huffman code table to pCodeTable. Returns the
// tileset's last tile id.
u32 DecodeBgTilesetOffsetTable(RoomBgResources resources, BgTileset *pTileset,
                                         BgTileCodeTable *pCodeTable)
{
    u32 codeOffset;
    u32 size;
    u8 *pLengths;
    const u8 *pCompressed;
    u32 tileCount;
    u32 lengthsSize;
    u32 count;
    u32 bitOffset;
    u32 *pBitOffset;
    const u8 *pLength;
    u32 length;
    u32 i;

    codeOffset = *(const u16 *)resources.pTileset;
    tileCount = *(const u16 *)(resources.pTileset + 2);
    pCompressed = resources.pTileset + 4;
    lengthsSize = GetResourceDecompressedSize(pCompressed);
    count = tileCount + 1;
    pTileset->pTileBitOffsets = AllocBlock(count * sizeof(u32));
    resources.pTileset += codeOffset;
    resources.pTileset += 8;
    pTileset->pRomCodeTable = (const BgTileCodeTable *)resources.pTileset;
    size = 0x124;
    pTileset->pCodeTable = pCodeTable;
    pLengths = AllocBlock(lengthsSize);
    DecompressResource(pCompressed, pLengths);
    pTileset->pTileData = (const u8 *)pTileset->pRomCodeTable + size;

    bitOffset = ((const u8 *)pTileset->pRomCodeTable + size - ROM_BASE) * 8;
    i = count;
    pBitOffset = pTileset->pTileBitOffsets;
    pLength = pLengths + 2;
    for (; i != 0; i--)
    {
        *pBitOffset = bitOffset;
        length = *pLength++;
        if (length == 0xFF)
        {
            length = *pLength++ << 8;
            length += *pLength++;
            bitOffset += length;
        }
        else
        {
            bitOffset += length + 0x20;
        }
        pBitOffset++;
    }

    memcpy(pTileset->pCodeTable, pTileset->pRomCodeTable, size);
    FreeBlock(pLengths);
    return tileCount;
}
