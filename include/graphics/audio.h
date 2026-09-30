#pragma once

#include "types.h"

// Sound effects and Krawall music playback.

// PlaySoundById's config row for a sound id.
typedef enum {
    SoundModeSample   = 1,  // play g_aSoundSamples[index]
    SoundModeVariants = 2,  // play one of the eight g_aSoundVariants[index] entries, chosen at random
} SoundMode;

typedef struct SoundConfigRow {
    u16 mode;   // SoundMode
    u16 index;
} SoundConfigRow;

#define SoundVariantNone 0xFF  // sampleIndex of a variant that plays nothing

typedef struct SoundSample {
    u16 sampleIndex;  // KrawallSamples index
    u16 freq;         // kramSetFreq argument
} SoundSample;

extern const SoundConfigRow g_aSoundConfig[179];       // 0x08FB09F8
extern const SoundSample g_aSoundSamples[164];         // 0x08FB0588
extern const SoundSample g_aSoundVariants[15][8];      // 0x08FB0818
extern void *const KrawallSamples[278];                // 0x08D229F4

// Thumb veneers into the Krawall IWRAM code: start a sample on a channel, returning its handle,
// and set that channel's frequency (kramSetFreq).
extern s32 sub_08049E40(void *sample, s32 arg1, s32 arg2);
extern void sub_08049E54(s32 handle, u32 freq);
extern s32 IsSoundActive_candidate(s32 handle);

extern s32 PlaySoundById(s32 id);  // returns a handle for StopSoundEffect
// Returns handle unchanged while it is still playing, otherwise plays the sound like PlaySoundById.
extern s32 PlaySoundByIdUnlessActive_candidate(s32 id, s32 handle);
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
