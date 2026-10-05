#include "types.h"
#include "graphics/audio.h"

void InitAudio(void)
{
    kragInit(KRAG_INIT_STEREO);
    kramSetMasterVol(KRAM_MV_CHANNELS16 | 128);
    kramQualityMode(KRAM_QM_HQ);
    SetSoundEffectVolume(0xFF);
    SetMusicVolume(0x7F, 0);
    ApplyAudioVolumeSettings();
    g_bCurrentMusicModule = 0xFF;
    g_bMusicPaused = 0;
    krapCallback(OnKrawallEvent);
}
