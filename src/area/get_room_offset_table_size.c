#include "types.h"
#include "area.h"

// Byte size of an offset array of `count` u16 entries, padded to a multiple of 4.
u16 GetRoomOffsetTableSize(u16 count)
{
    if (count & 1)
        count++;
    count *= 2;
    return count;
}
