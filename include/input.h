#pragma once

#include "types.h"

// Controller input state maintained by UpdateKeyInput (0x080254A8), called
// once per game-loop iteration from TickGameModeStack. See
// docs/memory-map/input.md for the full field list, standard GBA KEYINPUT
// bit layout, and known readers -- only the fields an existing matched
// c-file actually reads are declared here.

extern u16 g_wKeysHeld;             // 0x030034EC: current held-key bitmask
extern u16 g_wKeysHeldPrevious;     // 0x030034EE: g_wKeysHeld from the previous frame
extern u16 g_wKeysPressed;          // 0x030034F0: keys newly pressed this frame
extern u16 g_wKeysReleased;         // 0x030034F2: keys newly released this frame
extern u16 g_wInputDisabled;        // 0x030034F4: nonzero forces all key state to 0

extern u16 g_awPlayerKeysHeld[2];          // 0x030034F6: per-player held-key masks, link input path
extern u16 g_awPlayerKeysHeldPrevious[2];  // 0x030034FA: previous-frame counterpart of the above
extern u16 g_awPlayerKeysPressed[2];       // 0x030034FE: per-player newly-pressed masks
extern u16 g_awPlayerKeysReleased[2];      // 0x03003502: per-player newly-released masks

extern void UpdateKeyInput(void);
extern void ResetKeyInput(void);

extern u16 g_awLinkKeysReceived[2];  // 0x03005A0C: per-player key masks received over the link cable
