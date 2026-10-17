#pragma once

#include "types.h"

// BG tile animations: tiles decoded into a buffer each tick and uploaded to their BG's
// character block at vblank; see docs/memory-map/frame_systems.md.

// One frame of a BG tile animation: its tile data and how many ticks it shows
// (0 holds it).
typedef struct BgTileAnimFrame {
    const void *pTiles;
    u32 dwDuration;
} BgTileAnimFrame;

// A BG tile animation registered by RegisterBgTileAnimation and stepped by
// TickBgTileAnimations; see docs/memory-map/frame_systems.md.
#define BG_TILE_ANIMATION(frameCount) struct {                       \
    u8 bFlags;                                                        \
    u8 bFrameCount;                                                   \
    u16 wUnk2;            /* copied into the animation's entry */     \
    u32 dwBufferSize;     /* bytes allocated for the decoded tiles */ \
    BgTileAnimFrame aFrames[frameCount];                              \
}

// The fixed head of every BG_TILE_ANIMATION.
typedef struct BgTileAnimHeader {
    u8 bFlags;
    u8 bFrameCount;
    u16 wUnk2;
    u32 dwBufferSize;
} BgTileAnimHeader;

// The low bits of a BG control word as stored in ROM (the BGxCNT layout).
typedef struct BgControlWord {
    u32 bPriority : 2;
    u32 bCharBlock : 2;  // 16 KB character block holding the BG's tiles
    u32 dwRest : 28;
} BgControlWord;

// Runtime state of one registered BG tile animation.
typedef struct BgTileAnimEntry {
    u8 bFlags;  // 1 active, 2 running, 4 tiles pending upload, 8 buffer is uploaded in one piece
    u8 pad_01;
    u8 bFrame;
    u8 bTimer;
    u16 wTileOffset;  // first tile in the character block
    u16 pad_06;
    const BgTileAnimHeader *pAnimation;
    const BgControlWord *pBgControl;
} BgTileAnimEntry;

typedef BG_TILE_ANIMATION(16) BgTileAnimation16;
typedef BG_TILE_ANIMATION(64) BgTileAnimation64;
typedef BG_TILE_ANIMATION(128) BgTileAnimation128;

extern void RegisterBgTileAnimation(const void *pTable, const void *pBgControls, u32 count);
extern void TickBgTileAnimations(void);
extern void CommitBgTileAnimations(void);  // run from the vblank callback
extern void PauseBgTileAnimations(void);   // clears bit 1 (running) of every BG tile animation
extern void ResumeBgTileAnimations(void);  // sets bit 1 of every BG tile animation
extern void FreeBgTileAnimations(void);

extern u8 g_bBgTileAnimationCount;
extern BgTileAnimEntry g_aBgTileAnimations[4];
extern void *g_apBgTileAnimationBuffers[4];  // decoded tiles of each entry
