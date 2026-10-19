#include "sound.h"
#include "3rd_party/krawall.h"

void StopSoundEffect(s32 handle)
{
    kramStop(handle);
}
