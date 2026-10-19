#include "types.h"
#include "map.h"
#include "sound.h"
#include "sound_inline.h"
#include "3rd_party/krawall.h"

// Loops module `moduleId` unless it is already the current one. g_bCurrentMusicModule
// only records it while PauseMusic's pause is not in effect.
void PlayMusicModule(u8 moduleId)
{
    if (moduleId != g_bCurrentMusicModule)
    {
        krapPlay(g_apMusicModules[moduleId], KRAP_MODE_LOOP, 0);
        // Identical arms: the ROM keeps the room id read but not the tested value.
        if (g_bCurrentRoomId == 0)
            SetUnreadAudioValue(8);
        else
            SetUnreadAudioValue(8);
        if (!g_bMusicPaused)
            g_bCurrentMusicModule = moduleId;
    }
}
