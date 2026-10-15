// The classic newlib memset shape (byte-fill to alignment, word-fill the
// middle, byte-fill the remainder), but compiled as ordinary game code,
// not part of the vendored libc block src/libc/ matches.

#include "mem.h"

void *memset(void *dst0, int val, u32 len)
{
    u32 wordCount;
    u8 *ptr = dst0;
    u32 head = 4 - ((u32)dst0 & 3);
    u32 pattern;
    u32 tailCount;
    u32 i;

    if (head != 4) {
        if (len < head) {
            head = len;
        }
        for (i = 0; i < head; i++) {
            ptr[i] = val;
        }
        len -= i;
        ptr += i;
    }

    wordCount = len >> 2;
    pattern = (val << 8) | val;
    pattern |= pattern << 16;
    // Indexed, not a walking `*p++` -- see docs/memory-map/heap.md.
    for (i = 0; i < wordCount; i++) {
        ((u32 *)ptr)[i] = pattern;
    }
    ptr += i * 4;

    tailCount = len & 3;
    for (i = 0; i < tailCount; i++) {
        ptr[i] = val;
    }

    return dst0;
}
