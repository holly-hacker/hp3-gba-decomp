#include "commands.h"
#include "sound.h"
#include "overworld/room_script.h"

void RoomScriptOpPauseMusic(RoomScriptRecord *pRecord)
{
    PauseMusic();
}
