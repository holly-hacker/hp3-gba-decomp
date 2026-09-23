#pragma once

#include "types.h"

// Sound effects and Krawall music playback.

extern s32 PlaySoundById(s32 id);  // returns a handle for StopSoundEffect
extern void PlayMusicModule(u8 moduleId);
// Clears the mute flag on every active Krawall channel.
extern void UnmuteAllMusicChannels(void);
extern void PlaySoundEffect_candidate(u32 id);
extern void SetMusicVolume(u32 volume, u32 arg);
// Pause/resume the music module; ResumeMusic only acts if PauseMusic paused it.
extern void PauseMusic(void);
extern void ResumeMusic(void);
extern void StopMusic(void);
extern void StopSoundEffect(s32 handle);

extern u8 g_bMusicPaused;         // 0x03005AC1: set by PauseMusic
extern u8 g_bCurrentMusicModule;  // 0x03005AC2: last module started by PlayMusicModule, 0xFF if none
extern void SetSoundEffectVolume(u32 volume);
extern void DisableKrawall(void);
extern void EnableKrawall(void);
