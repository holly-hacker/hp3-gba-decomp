#include "types.h"
#include "area.h"

// `size` rounded up to a multiple of 4.
u16 AlignRoomSizeTo4(u16 size)
{
    u16 pad;

    pad = size & 3;
    if (pad == 1)
        pad = 3;
    else if (pad == 2)
        pad = 2;
    else if (pad == 3)
        pad = 1;
    return size + pad;
}
