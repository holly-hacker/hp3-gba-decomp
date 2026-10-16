#include "types.h"
#include "commands.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

void RoomScriptOpUnmuteAllMusicChannels(RoomScriptRecord *pRecord)
{
    UnmuteAllMusicChannels();
}
