#include "sound.h"
#include "3rd_party/krawall.h"

void ResumeMusic(void)
{
    if (g_bMusicPaused)
    {
        krapUnpause();
        g_bMusicPaused = 0;
    }
}
