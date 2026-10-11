#include "types.h"
#include "text.h"

// Appends pSrc to the end of pDest and returns pDest.
u8 *AppendString(u8 *pDest, const u8 *pSrc)
{
    u8 *pEnd;

    pEnd = pDest;
    while (*pEnd != 0)
        pEnd++;
    while (*pSrc != 0)
        *pEnd++ = *pSrc++;
    *pEnd = *pSrc;
    return pDest;
}
