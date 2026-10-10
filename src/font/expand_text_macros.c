#include "types.h"
#include "font.h"

// Copies pSrc to pDest with each 0x40-prefixed macro code replaced by its
// sTextMacroTable string, writing at most maxLen bytes before the terminator.
// Macros do not nest: a 0x40 inside a macro string is never advanced past.
u8 *ExpandTextMacros(u8 *pDest, const u8 *pSrc, s32 maxLen)
{
    u8 *pStart;
    const u8 *pMacro;

    pStart = pDest;
    while (*pSrc != 0 && maxLen != 0)
    {
        if (*pSrc == 0x40)
        {
            pSrc++;
            pMacro = sTextMacroTable[*pSrc++ - 0x31];
            while (*pMacro != 0 && maxLen != 0)
            {
                if (*pMacro != 0x40)
                {
                    if (*pMacro > 0xEF)
                    {
                        *pDest++ = *pMacro++;
                        maxLen--;
                    }
                    *pDest++ = *pMacro++;
                    maxLen--;
                }
            }
        }
        else
        {
            if (*pSrc > 0xEF)
            {
                *pDest++ = *pSrc++;
                maxLen--;
            }
            *pDest++ = *pSrc++;
            maxLen--;
        }
    }
    *pDest = 0;
    return pStart;
}
