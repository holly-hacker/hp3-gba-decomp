#pragma once

#include "types.h"

// The save-data checksum: the 16-bit sum of size/2 halfwords. A region is
// valid when its halfwords, including its trailing checksum word, sum to 0.
//
// The ROM calls Sum16 out of line from the slot code that precedes it and
// inlines it into the header/options functions that follow it, as one
// translation unit with an inline Sum16 would. Those later functions include
// this header; src/save/sum16.c defines SUM16_LINKAGE as empty to emit the
// out-of-line copy, which everything else calls through game/save.h.
#ifndef SUM16_LINKAGE
#define SUM16_LINKAGE extern inline
#endif

SUM16_LINKAGE u16 Sum16(const void *data, u32 size)
{
    const u16 *pData = data;
    u16 sum = 0;
    s32 count;

    for (count = size / 2; count > 0; count--)
        sum += *pData++;

    return sum;
}
