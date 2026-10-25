#pragma once

#include "types.h"
#include "3rd_party/krawall.h"

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
    u16 sampleIndex;  // samples index
    u16 freq;         // kramSetFreq argument
} SoundSample;

extern const SoundConfigRow g_aSoundConfig[179];
extern const SoundSample g_aSoundSamples[164];
extern const SoundSample g_aSoundVariants[15][8];

// Music and jingle modules by module id (PlayMusicModule, PlayJingle).
extern const Module *const g_apMusicModules[52];

extern s32 IsSoundActive(s32 handle);

extern s32 PlaySoundById(s32 id);  // returns a handle for StopSoundEffect
// Returns handle unchanged while it is still playing, otherwise plays the sound like PlaySoundById.
extern s32 PlaySoundByIdUnlessActive(s32 id, s32 handle);
extern void PlayMusicModule(u8 moduleId);
// Both stop every playing sound effect (kramStopSFXChannels); the bodies are identical.
extern void StopSoundEffectChannels(void);
extern void StopAllSoundEffects(void);
extern void PlayJingle(u8 moduleId);
extern void SetMusicVolume(u8 volume, u32 fade);
// Pause/resume the music module; ResumeMusic only acts if PauseMusic paused it.
extern void PauseMusic(void);
extern void ResumeMusic(void);
extern void StopMusic(void);
extern void StopSoundEffect(s32 handle);

extern u8 g_bMusicPaused;         // 0x03005AC1: set by PauseMusic
extern u8 g_bCurrentMusicModule;  // 0x03005AC2: last module started by PlayMusicModule, 0xFF if none
extern void SetSoundEffectVolume(u8 volume);

// Audio startup: kramInstall copies the RAM sections and calls InitAudio.
extern u8 g_bUnreadAudioValue;  // set to 8 by kramInstall and PlayMusicModule; nothing reads it
extern void kramInstall(void);
extern void InitAudio(void);
extern void ApplyAudioVolumeSettings(void);
extern void OnKrawallEvent(s32 event, s32 param);

extern void DisableKrawall(void);
extern void EnableKrawall(void);
extern void DisableKrawallTimerInterrupt(void);
extern void EnableKrawallTimerInterrupt(void);

extern void SetUnreadAudioValue(u8 value);

// No callers.
extern void DisableKrawall_unused(void);
extern void SoundNop(void);
extern void PauseMusic_unused(void);

// Start/end of the statically linked IWRAM and EWRAM sections: Krawall's ARM
// mixer code and its engine state. kramInstall copies their ROM images to RAM;
// ClearWorkRam zeroes the RAM above them through the pointer constants.
extern u8 g_KrawallIwramStart[];  // 0x03000000
extern u8 g_KrawallIwramEnd[];    // 0x03001598
extern u8 g_KrawallEwramStart[];  // 0x02000000
extern u8 g_KrawallEwramEnd[];    // 0x020027F8
// ROM images of those sections, stored back to back.
extern const u8 g_KrawallIwramRomImage[];
extern const u8 g_KrawallEwramRomImage[];
extern u8 *const g_pKrawallIwramStart;
extern u8 *const g_pKrawallIwramEnd;
extern u8 *const g_pKrawallEwramStart;
extern u8 *const g_pKrawallEwramEnd;
