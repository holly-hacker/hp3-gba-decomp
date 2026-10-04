#include "types.h"
#include "hw/eeprom.h"
#include "game/save.h"

// Writes count consecutive 8-byte EEPROM blocks starting at startBlock from
// src, verifying (and retrying) each block.
void EepromWriteBlocks(u32 startBlock, u32 count, const void *src)
{
    const u16 *pSrc = src;

    EepromTransferBegin();
    while (count != 0)
    {
        EepromWriteBlockVerified(startBlock, pSrc);
        pSrc += 4;
        startBlock++;
        count--;
    }
    EepromTransferEnd();
}
