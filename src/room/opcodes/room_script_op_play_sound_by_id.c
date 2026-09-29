#include "types.h"
#include "graphics/audio.h"
#include "overworld/room_script.h"

typedef struct PlaySoundByIdRecord {
    u32 dwOpcode;
    u8 bSoundId;
} PlaySoundByIdRecord;

void RoomScriptOpPlaySoundById(PlaySoundByIdRecord *pRecord)
{
    PlaySoundById(pRecord->bSoundId);
}
