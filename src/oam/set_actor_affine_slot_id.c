#include "types.h"
#include "actor.h"

void SetActorAffineSlotId(OamEntry *oam, u16 slot)
{
    OAM_ATTR1(oam) = (OAM_ATTR1(oam) & 0xC1FF) | (slot << 9);
}
