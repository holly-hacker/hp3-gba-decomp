#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/menus.h"

typedef struct {
    Actor *pPortraitActor;  // 0x00: sprite showing the selected portrait
    u32 dwSelection;          // 0x04: portrait index, 0..0x86
} CheatPortraitsState;

extern CheatPortraitsState g_CheatPortraitsState;  // 0x03002210
extern const u32 g_dwCheatPortraitsBg1Control;  // 0x0804C618

extern void ShowCheatPortrait(void);
