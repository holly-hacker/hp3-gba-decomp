#pragma once

#include "types.h"

extern void *const KrawallSamples[278];                // 0x08D229F4

// Thumb veneers into the Krawall IWRAM code: run the mixer (kramWorker, run at vblank), start a
// sample on a channel, returning its handle, and set that channel's frequency (kramSetFreq).
extern void kramWorkerVeneer_candidate(void);
extern s32 kramPlayVeneer(void *sample, s32 arg1, s32 arg2);
extern void kramSetFreqVeneer(s32 handle, u32 freq);

// Krawall library entry points called by the startup code, identified against
// the public Krawall API; see docs/memory-map/krawall.md.
#define KRAG_INIT_STEREO   1
#define KRAM_QM_HQ         2
#define KRAM_MV_CHANNELS16 (4 << 16)
#define KRAP_CB_JDONE      5  // krapCallback event: jingle finished
extern void kragInit(u32 stereo);
extern void kramSetMasterVol(u32 volume);
extern void kramQualityMode(u32 mode);
extern void kramSetSFXVol(u32 volume);
extern void krapCallback(void (*callback)(s32 event, s32 param));
extern void krapSetMusicVol(u32 volume, u32 fade);
