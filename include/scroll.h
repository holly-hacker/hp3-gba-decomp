#pragma once

#include "types.h"
#include "camera.h"

// World-space camera origin used for actor visibility.
extern CameraFocusOffset g_CameraPosition_candidate;

// Pixel size of the current room.
typedef struct RoomSizePixels {
    u32 dwWidth;
    u32 dwHeight;
} RoomSizePixels;

extern RoomSizePixels g_RoomSizePixels;

// Updates g_CameraPosition_candidate from the followed actor and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera_candidate(u32 mode);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void LoadRoomBgLayer0Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
