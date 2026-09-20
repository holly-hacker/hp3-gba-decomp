#include "types.h"
#include "audio.h"
#include "room_script.h"

void RoomScriptOpSetSoundEffectVolume(RoomScriptRecord *pRecord)
{
    SetSoundEffectVolume(pRecord->operand.ab[0]);
}
