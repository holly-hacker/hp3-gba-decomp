#include "types.h"
#include "game/save.h"
#include "graphics/audio.h"

// Applies the saved options-menu volumes (0-10 each).
void ApplyAudioVolumeSettings(void)
{
    SetSoundEffectVolume(g_saveManager.header.bMusicVolume * 25);
    SetMusicVolume(g_saveManager.header.bSoundVolume * 12, 0);
}
