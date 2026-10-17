#include "types.h"
#include "commands.h"
#include "sound.h"

typedef struct SetRoomMusicVolumeRecord {
    u32 dwOpcode;
    u8 bVolume;
} SetRoomMusicVolumeRecord;

void RoomScriptOpSetRoomMusicVolume(SetRoomMusicVolumeRecord *pRecord)
{
    SetMusicVolume(pRecord->bVolume, 1);
}
