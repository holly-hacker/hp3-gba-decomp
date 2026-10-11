#include "actor.h"

u8 GetFrameCellCount(ActorFrameDesc *frameDesc)
{
    return frameDesc->bCellCount & 0x1F;
}
