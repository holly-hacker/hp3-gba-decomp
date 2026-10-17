#include "types.h"
#include "commands.h"
#include "sound.h"

typedef struct PlaySoundByIdRecord {
    u32 dwOpcode;
    u8 bSoundId;
} PlaySoundByIdRecord;

void RoomScriptOpPlaySoundById(PlaySoundByIdRecord *pRecord)
{
    PlaySoundById(pRecord->bSoundId);
}
