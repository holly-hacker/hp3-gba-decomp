#pragma once

#include "types.h"
#include "graphics/display.h"

// BG tile animations: tiles decoded into a buffer each tick and uploaded to their BG's
// character block at vblank; see docs/memory-map/frame_systems.md.

extern void RegisterBgTileAnimation(const void *pTable, const void *pBgControls, u32 count);
extern void TickBgTileAnimations(void);
extern void CommitBgTileAnimations(void);  // run from the vblank callback
extern void PauseBgTileAnimations(void);   // clears bit 1 (running) of every BG tile animation
extern void ResumeBgTileAnimations(void);  // sets bit 1 of every BG tile animation
extern void FreeBgTileAnimations(void);
