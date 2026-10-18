#include "types.h"
#include "sound.h"
#include "3rd_party/krawall.h"

void SetMusicVolume(u8 volume, u32 fade)
{
    krapSetMusicVol(volume, fade);
}
