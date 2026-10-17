#include "types.h"
#include "sound.h"
#include "krawall.h"

void SetMusicVolume(u8 volume, u32 fade)
{
    krapSetMusicVol(volume, fade);
}
