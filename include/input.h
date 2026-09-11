#pragma once

#include "types.h"

// Controller input state maintained by UpdateKeyInput (0x080254A8), called
// once per game-loop iteration from TickGameModeStack. See
// docs/memory-map/input.md for the full field list, standard GBA KEYINPUT
// bit layout, and known readers -- only the fields an existing matched
// c-file actually reads are declared here.

extern u16 g_wKeysHeld;      // 0x030034EC: current held-key bitmask
extern u16 g_wKeysPressed;   // 0x030034F0: keys newly pressed this frame

extern void UpdateKeyInput(void);
