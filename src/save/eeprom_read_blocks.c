#include "types.h"
#include "hw/eeprom.h"
#include "game/save.h"

// Reads count consecutive 8-byte EEPROM blocks starting at startBlock into dst.
void EepromReadBlocks(u32 startBlock, u32 count, void *dst)
{
    u16 *pDst = dst;

    EepromTransferBegin();
    while (count != 0)
    {
        EepromReadBlock(startBlock, pDst);
        pDst += 4;
        startBlock++;
        count--;
    }
    EepromTransferEnd();
}
