#include "types.h"
#include "area.h"

// Whether row `row` may run: never row 0, nor row 1 while the room has a default group.
u32 ShouldRunRoomIndex(u8 row)
{
    if ((g_wRoomVariantFlags & 1) && row == 1)
        return 0;
    if (row == 0)
        return 0;
    return 1;
}
