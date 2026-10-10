#include "types.h"
#include "font.h"

void SetTextMacro4String(const u8 *pString)
{
    u8 *pDest;

    pDest = sTextMacroTable[3];
    while (*pString != 0)
    {
#ifdef VERSION_JP
        if (*pString > 0xEF)
            *pDest++ = *pString++;
#endif
        *pDest++ = *pString++;
    }
    *pDest = 0;
}
