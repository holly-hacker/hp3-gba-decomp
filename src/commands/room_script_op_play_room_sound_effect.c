#include "types.h"
#include "modes.h"
#include "commands.h"
#include "sound.h"
#include "area.h"
#include "main.h"

typedef struct PlayRoomSoundEffectRecord {
    u32 dwOpcode;
    u8 bSoundId;
} PlayRoomSoundEffectRecord;

void RoomScriptOpPlayRoomSoundEffect(PlayRoomSoundEffectRecord *pRecord)
{
    // InitializeOverworld clears this bit and skips its room-music selection when it is set.
    if (g_bRoomScriptCurrentChain == 1)
        g_dwGameModeFlags |= GameModeFlagKeepScriptMusic;
    PlayJingle(pRecord->bSoundId);
}
