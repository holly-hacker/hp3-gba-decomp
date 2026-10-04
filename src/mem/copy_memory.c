#include "types.h"
#include "hw/mem.h"

// Copies len bytes, a word at a time when both pointers are word-aligned.
void *CopyMemory(void *dst, const void *src, u32 len)
{
    const u8 *pSrc = src;
    u8 *pDst = dst;
    u32 i;
    u32 wordCount;
    s32 tailCount;

    if (((u32)dst & 3) || ((u32)src & 3))
    {
        for (i = 0; i < len; i++)
            pDst[i] = pSrc[i];
    }
    else
    {
        wordCount = len >> 2;
        for (i = 0; i < wordCount; i++)
            ((u32 *)dst)[i] = ((const u32 *)src)[i];

        tailCount = len & 3;
        i = len - tailCount;
        while (tailCount--)
        {
            pDst[i] = pSrc[i];
            i++;
        }
    }

    return dst;
}
