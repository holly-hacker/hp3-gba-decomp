#include "types.h"
#include "display.h"
#include "room_script.h"

void RoomScriptOpSetScreenWindow(RoomScriptRecord *pRecord)
{
    SetScreenWindowLayers_candidate(pRecord->operand.ab[0], pRecord->operand.ab[10], pRecord->operand.ab[11]);
    SetScreenWindowRect_candidate(pRecord->operand.ab[0], pRecord->operand.asw[1] << 16,
                                  pRecord->operand.asw[2] << 16, pRecord->operand.asw[3] << 16,
                                  pRecord->operand.asw[4] << 16);
}
