#include "types.h"
#include "sound.h"
#include "3rd_party/krawall.h"

void SetSoundEffectVolume(u8 volume)
{
    kramSetSFXVol(volume);
}
