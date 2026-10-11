#include "types.h"
#include "graphics/text.h"
#include "text.h"

// Decodes dialog string stringId onto the end of pDest. Returns pDest, or 0
// if the string could not be decoded.
u8 *AppendDialogText(u8 *pDest, s32 stringId)
{
    u8 *pEnd;

    pEnd = pDest;
    while (*pEnd != 0)
        pEnd++;
    if (DecompressDialogText(stringId, pEnd, 0x400) == DialogTextOk)
        return pDest;
    return 0;
}
