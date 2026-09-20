#pragma once

#include "types.h"

// Sound effects and Krawall music playback.

extern void PlaySoundById(s32 id);
extern void PlayMusicModule(u8 moduleId);
// Clears the mute flag on every active Krawall channel.
extern void UnmuteAllMusicChannels(void);
extern void PlaySoundEffect_candidate(u32 id);
extern void SetMusicVolume(u32 volume, u32 arg);
// Pause/resume the music module; ResumeMusic only acts if PauseMusic paused it.
extern void PauseMusic(void);
extern void ResumeMusic(void);
extern void SetSoundEffectVolume(u32 volume);
