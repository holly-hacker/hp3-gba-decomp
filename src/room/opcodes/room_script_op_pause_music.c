#include "types.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

void RoomScriptOpPauseMusic(RoomScriptRecord *pRecord)
{
    PauseMusic();
}
