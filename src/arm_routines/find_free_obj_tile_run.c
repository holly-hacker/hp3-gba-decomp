#include "arm_routines.h"

// Returns the first bit of the first run of runLength clear bits at or after
// bit, or 0xFFFF if none ends within bit 0x400.
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 bit)
{
    u32 start;
    s32 remaining;
    u32 shift;
    u8 bits;

    do {
        remaining = runLength;
        start = bit;
        for (;;) {
            bits = pBitmap[bit >> 3];
            if (bits == 0xFF) {
                bit += 8;
                break;
            }
            if (bits == 0) {
                bit += 8;
                remaining -= 8;
                if (remaining <= 0)
                    return start;
                continue;
            }
            shift = bit & 7;
        nextBit:
            bit++;
            if (bits >> shift & 1)
                break;
            if (--remaining <= 0)
                return start;
            if (++shift <= 7)
                goto nextBit;
        }
    } while (bit + runLength <= 0x400);
    return 0xFFFF;
}
