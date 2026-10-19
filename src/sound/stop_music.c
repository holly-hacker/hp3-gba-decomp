#include "sound.h"
#include "3rd_party/krawall.h"

void StopMusic(void)
{
    krapStop();
    g_bMusicPaused = 0;
}
