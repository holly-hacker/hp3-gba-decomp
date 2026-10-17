#pragma once

#include "types.h"
#include "gen/graphics/cutscenes.h"
#include "gen/graphics/minigames/hippogriff.h"

// Display registers and BG layers. sub_ names are still unidentified.

// Per-frame ticks run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickScreenWindows_candidate(void);

// The colors of a graphic blob's embedded palette, after its two flag bytes
// (see docs/formats/graphic_blob.md).
#define GRAPHIC_BLOB_PALETTE_COLORS(blob) ((const u16 *)((const u8 *)(blob) + 2))

// One corner of a hardware window rectangle, positions in 16.16.
typedef struct WindowCorner {
    u16 wFlags;       // bit 1: moving toward the target or drifting
    u16 wFrames;      // frames left in the tween; 0 drifts by the step every frame
    s32 nX;
    s32 nY;
    s32 nStepX;       // per-frame drift, used while wFrames is 0
    s32 nStepY;
    s32 nTargetX;
    s32 nTargetY;
} WindowCorner;

// A hardware window: its top-left and bottom-right corners.
typedef struct ScreenWindow {
    u32 dwFlags;      // bit 0: rectangle changed, needs writing to WINxH/WINxV
    WindowCorner aCorners[2];
} ScreenWindow;
extern ScreenWindow g_aScreenWindows[2];

extern void TickScreenWindow(u32 windowId);

// Hardware windows: layer masks, rectangle (16.16 coordinates), and hiding one.
extern void SetScreenWindowLayers_candidate(u32 windowId, u32 winIn, u32 winOut);
extern void SetScreenWindowRect_candidate(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);
extern void HideScreenWindow_candidate(u32 windowId);

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

extern u8 g_bBgTileAnimationCount;
extern BgTileAnimEntry g_aBgTileAnimations[4];
extern void *g_apBgTileAnimationBuffers[4];  // decoded tiles of each entry

typedef BG_TILE_ANIMATION(16) BgTileAnimation16;
typedef BG_TILE_ANIMATION(64) BgTileAnimation64;
typedef BG_TILE_ANIMATION(128) BgTileAnimation128;


// The write-only half of SetBgControl: writes BGxCNT and the tilemap/charblock
// VRAM bases, without enabling the layer via SetDispcntFlag.
extern void SetBgControlRegister(u32 bg, u32 control);
