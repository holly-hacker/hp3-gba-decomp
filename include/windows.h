#pragma once

#include "types.h"

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

// Hardware windows: hiding one, layer masks, and rectangle (16.16 coordinates).
extern void HideScreenWindow_candidate(u32 windowId);
extern void SetScreenWindowLayers_candidate(u32 windowId, u32 winIn, u32 winOut);
extern void SetScreenWindowRect_candidate(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);
// Run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickScreenWindows_candidate(void);
extern void sub_08045988(void);  // writes the window rects to WINxH/WINxV at vblank
extern void TickScreenWindow(u32 windowId);
