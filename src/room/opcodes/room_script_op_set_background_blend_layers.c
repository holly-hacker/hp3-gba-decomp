#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpSetBackgroundBlendLayers(RoomScriptRecord *pRecord)
{
    SetAlphaBlendTargets((pRecord->operand.ab[1] << 1) | pRecord->operand.ab[0] | (pRecord->operand.ab[2] << 2)
                     | (pRecord->operand.ab[3] << 3),
                 0x1f);
}
