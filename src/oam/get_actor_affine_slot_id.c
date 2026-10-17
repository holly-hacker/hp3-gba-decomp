#include "types.h"
#include "oam.h"

u32 GetActorAffineSlotId(OamEntry *oam)
{
    return (OAM_ATTR1(oam) >> 9) & 0x1F;
}
