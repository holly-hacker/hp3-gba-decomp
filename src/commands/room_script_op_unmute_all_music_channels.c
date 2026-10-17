#include "commands.h"
#include "sound.h"
#include "overworld/room_script.h"

void RoomScriptOpUnmuteAllMusicChannels(RoomScriptRecord *pRecord)
{
    UnmuteAllMusicChannels();
}
