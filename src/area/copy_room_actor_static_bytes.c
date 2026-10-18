#include "types.h"
#include "area.h"

// Copies `size` bytes of a record's static data past its 8-byte runtime prefix.
void CopyRoomActorStaticBytes(const u8 *pSrc, u8 *pDst, u8 size)
{
    u8 i;

    pDst += 8;
    for (i = 0; i < size; i++)
        *pDst++ = *pSrc++;
}
