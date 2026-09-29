#include "types.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

typedef struct SetRoomMusicVolumeRecord {
    u32 dwOpcode;
    u8 bVolume;
} SetRoomMusicVolumeRecord;

void RoomScriptOpSetRoomMusicVolume(SetRoomMusicVolumeRecord *pRecord)
{
    SetMusicVolume(pRecord->bVolume, 1);
}
