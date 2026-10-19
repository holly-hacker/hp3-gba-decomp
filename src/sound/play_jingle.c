#include "sound.h"
#include "3rd_party/krawall.h"

// Plays module `moduleId` once over the music (KRAP_MODE_JINGLE); OnKrawallEvent fades the
// music back in when it ends.
void PlayJingle(u8 moduleId)
{
    krapPlay(g_apMusicModules[moduleId], KRAP_MODE_JINGLE, 0);
}
