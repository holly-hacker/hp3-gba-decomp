#include "types.h"
#include "audio.h"
#include "room_script.h"

void RoomScriptOpPlaySoundById(RoomScriptRecord *pRecord)
{
    PlaySoundById(pRecord->operand.ab[0]);
}
