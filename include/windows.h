#pragma once

#include "types.h"
#include "math.h"

// One corner of a hardware window rectangle, positions in 16.16.
typedef struct WindowCorner {
    u16 wFlags;         // bit 1: moving toward the target or drifting
    u16 wFrames;        // frames left in the tween; 0 drifts by the step every frame
    FixedPoint pos;
    FixedPoint step;    // per-frame drift, used while wFrames is 0
    FixedPoint target;
} WindowCorner;

// A hardware window: its top-left and bottom-right corners.
typedef struct ScreenWindow {
    u32 dwFlags;      // bit 0: rectangle changed, needs writing to WINxH/WINxV
    WindowCorner aCorners[2];
} ScreenWindow;
extern ScreenWindow g_aScreenWindows[2];

// DISPCNT enable bit of each window.
extern const u16 g_awScreenWindowDispcntFlags[2];

// Window 0 box wipes over window 1's rectangle, which they leave in place and
// show alongside window 0.
extern void ExpandScreenWindowFromCenter(u16 frames);
extern void ShrinkScreenWindowToCenter(u16 frames);

// Hardware windows: showing and hiding one, layer masks, and rectangle (16.16 coordinates).
extern void HideScreenWindow(u32 windowId);
extern void ShowScreenWindow(u32 windowId);
extern void SetScreenWindowLayers(u32 windowId, u16 winIn, u16 winOut);  // also shows the window
extern void SetScreenWindowRect(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1);

// Corner motion, advanced by TickScreenWindow.
extern void TweenScreenWindowCorner(u32 windowId, u32 corner, s32 x, s32 y, u16 frames);
extern void SetScreenWindowCorner(u32 windowId, u32 corner, s32 x, s32 y);
extern void DriftScreenWindowCorner(u32 windowId, u32 corner, s32 stepX, s32 stepY);

// Run by TickFrameSystems; see docs/memory-map/frame_systems.md.
extern void TickScreenWindows(void);
extern void WriteScreenWindowRects(void);  // writes changed rects to WINxH/WINxV at vblank
extern void HideScreenWindows(void);
extern void SetScreenWindowsLayers(u16 win0In, u16 win1In, u16 winOut);
extern void SetScreenWindow1Rect(s32 x0, s32 y0, s32 x1, s32 y1);
extern void TickScreenWindow(u32 windowId);
