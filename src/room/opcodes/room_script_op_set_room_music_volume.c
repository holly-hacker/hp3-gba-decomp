#include "types.h"
#include "audio.h"
#include "room_script.h"

void RoomScriptOpSetRoomMusicVolume(RoomScriptRecord *pRecord)
{
    SetMusicVolume(pRecord->operand.ab[0], 1);
}
