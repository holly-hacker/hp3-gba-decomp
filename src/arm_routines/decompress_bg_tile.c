#include "arm_routines.h"
#include "hw/io_regs.h"

// Decodes size bytes of a canonical-Huffman BG tile stream that starts
// bitOffset bits into the ROM. Symbols are paired into halfwords, low byte
// first; pending is 0x100 while no low byte is waiting.
void DecompressBgTile(u32 bitOffset, u16 *pDest, s32 size, const BgTileCodeTable *pTable)
{
    const u32 *pSrc;
    u32 buffer;
    s32 bitsLeft;
    s32 halfwords;
    u32 pending;
    u32 shift;
    u32 length;
    s32 code;
    u32 symbol;
    const u8 *pFirst;
    const u8 *pSymbols;

    pending = 0x100;
    halfwords = size >> 1;
    shift = bitOffset & 0x1F;
    bitsLeft = 31 - shift;
    pSrc = (const u32 *)(ROM_BASE + ((bitOffset >> 3) & ~3));
    pSymbols = pTable->abSymbols;
    buffer = *pSrc++;
    buffer >>= shift;
    pFirst = pTable->abFirst;
    while (halfwords > 0) {
        code = 0;
        for (length = 0; ; length++) {
            code = (code << 1) | (buffer & 1);
            if (--bitsLeft == -1) {
                buffer = *pSrc++;
                bitsLeft = 31;
            }
            else
                buffer >>= 1;
            if (code >= pTable->abCount[length]) {
                code -= pTable->abCount[length];
                continue;
            }
            symbol = code;
            break;
        }
        symbol = pSymbols[pFirst[length] + symbol];
        if (pending != 0x100) {
            halfwords--;
            *pDest++ = pending + (symbol << 8);
            pending = 0x100;
        }
        else
            pending = symbol;
    }
}
