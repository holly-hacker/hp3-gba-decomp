#include "types.h"
#include "overworld/room.h"

// Returns the block id stored in the room's BG block map entry covering pixel (x, y) on `layer`.
u16 GetRoomBgBlockEntry(u16 x, u16 y, u8 layer)
{
    return *GetRoomBgBlockMapEntryPtr(x, y, layer);
}
