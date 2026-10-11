#include "types.h"
#include "actor.h"

u32 GetObjectAffineSlotId(OamEntry *oam)
{
    return (OAM_ATTR1(oam) >> 9) & 0x1F;
}
