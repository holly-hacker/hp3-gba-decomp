#include "types.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

typedef struct SetSoundEffectVolumeRecord {
    u32 dwOpcode;
    u8 bVolume;
} SetSoundEffectVolumeRecord;

// The volume lands in a global (DAT_03000091) with no located reader.
void RoomScriptOpSetSoundEffectVolume(SetSoundEffectVolumeRecord *pRecord)
{
    SetSoundEffectVolume(pRecord->bVolume);
}
