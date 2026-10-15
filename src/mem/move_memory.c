#include "mem.h"

// CopyMemory for buffers that may overlap: copies backwards unless src lies
// after dst or the whole source range ends before dst. The backward word
// path copies its 0-3 leftover bytes from the start of the buffers instead
// of the end.
void *MoveMemory(void *dst, const void *src, u32 len)
{
    if ((const u8 *)src + len < (u8 *)dst || src > dst)
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
    else
    {
        const u8 *pSrc = src;
        u8 *pDst = dst;
        s32 i;
        s32 tailIndex;

        if (((u32)dst & 3) || ((u32)src & 3))
        {
            for (i = len - 1; i >= 0; i--)
                pDst[i] = pSrc[i];
        }
        else
        {
            for (i = (len >> 2) - 1; i >= 0; i--)
                ((u32 *)dst)[i] = ((const u32 *)src)[i];

            i = len & 3;
            tailIndex = i - 1;
            while (i--)
            {
                pDst[tailIndex] = pSrc[tailIndex];
                tailIndex--;
            }
        }
    }

    return dst;
}
