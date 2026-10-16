#include "types.h"
#include "commands.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

void RoomScriptOpResumeMusic(RoomScriptRecord *pRecord)
{
    ResumeMusic();
}
