#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "overworld/room_script.h"

typedef struct PlayRoomSoundEffectRecord {
    u32 dwOpcode;
    u8 bSoundId;
} PlayRoomSoundEffectRecord;

void RoomScriptOpPlayRoomSoundEffect(PlayRoomSoundEffectRecord *pRecord)
{
    // InitializeOverworld clears this bit and skips its room-music selection when it is set.
    if (g_bRoomScriptCurrentRow == 1)
        g_dwGameModeFlags |= 0x1000000;
    PlaySoundEffect_candidate(pRecord->bSoundId);
}
