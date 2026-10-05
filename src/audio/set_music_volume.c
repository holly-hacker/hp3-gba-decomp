#include "types.h"
#include "graphics/audio.h"

void SetMusicVolume(u8 volume, u32 fade)
{
    krapSetMusicVol(volume, fade);
}
