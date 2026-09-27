#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "room_script.h"

typedef struct PlayRoomSoundEffectRecord {
    u32 dwOpcode;
    u8 bSoundId;
} PlayRoomSoundEffectRecord;

void RoomScriptOpPlayRoomSoundEffect(PlayRoomSoundEffectRecord *pRecord)
{
    if (g_bRoomScriptCurrentRow == 1)
        g_dwGameModeFlags |= 0x1000000;
    PlaySoundEffect_candidate(pRecord->bSoundId);
}
