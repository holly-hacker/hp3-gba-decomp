#include "types.h"
#include "save.h"
#include "sound.h"
#include "3rd_party/krawall.h"

// Registered with krapCallback by InitAudio. When a jingle finishes, the
// music restarts at a quarter of the saved volume and fades back up.
void OnKrawallEvent(s32 event, s32 param)
{
    if (event == KRAP_CB_JDONE)
    {
        krapSetMusicVol(g_saveManager.header.bSoundVolume * 3, 0);
        krapSetMusicVol(g_saveManager.header.bSoundVolume * 12, 1);
    }
}
