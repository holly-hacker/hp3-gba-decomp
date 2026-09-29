#include "types.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

void RoomScriptOpUnmuteAllMusicChannels(RoomScriptRecord *pRecord)
{
    UnmuteAllMusicChannels();
}
