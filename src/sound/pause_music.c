#include "sound.h"
#include "3rd_party/krawall.h"

// Pauses the music (not sound effects) unless Krawall is already paused, in which case
// g_bMusicPaused stays clear and ResumeMusic leaves that pause alone.
void PauseMusic(void)
{
    g_bMusicPaused = krapIsPaused();
    if (!g_bMusicPaused)
    {
        krapPause(0);
        g_bMusicPaused = 1;
    }
}
