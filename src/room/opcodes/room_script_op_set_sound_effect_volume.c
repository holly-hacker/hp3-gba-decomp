#include "types.h"
#include "audio.h"
#include "room_script.h"

typedef struct SetSoundEffectVolumeRecord {
    u32 dwOpcode;
    u8 bVolume;
} SetSoundEffectVolumeRecord;

void RoomScriptOpSetSoundEffectVolume(SetSoundEffectVolumeRecord *pRecord)
{
    SetSoundEffectVolume(pRecord->bVolume);
}
