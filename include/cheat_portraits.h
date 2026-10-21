#pragma once

#include "types.h"
#include "actor.h"

// Portrait records the cheat menu pages through; only the first 72 are filled.
#define CHEAT_PORTRAIT_COUNT 135

typedef struct {
    Actor *pPortraitActor;  // 0x00: sprite showing the selected portrait
    u32 dwSelection;          // 0x04: portrait index, 0..CHEAT_PORTRAIT_COUNT-1
} CheatPortraitsState;

extern CheatPortraitsState g_CheatPortraitsState;  // 0x03002210
extern const u32 g_dwCheatPortraitsBg1Control;  // 0x0804C618
extern const ActorAssetRecord g_apPortraitTable[CHEAT_PORTRAIT_COUNT];  // US 0x0804C61C

extern void InitializeCheatPortraits(void);
extern void UpdateCheatPortraits(void);
extern void ExitCheatPortraits(void);

extern void ShowCheatPortrait(void);
