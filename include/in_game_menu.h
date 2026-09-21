#pragma once

#include "types.h"
#include "game_modes.h"

// One row of the pause menu, 12 bytes each.
typedef struct {
    GameMode mode;     // 0x00: mode pushed when the row is chosen
    u32 dwStringId;    // 0x04: row label
    u32 dwImmediate;   // 0x08: nonzero pushes the mode right away with a screen transition
} InGameMenuEntry;

extern const InGameMenuEntry g_aInGameMenuEntries[6];  // 0x08068C38
extern const u8 g_InGameMenuDefinition[];              // 0x08068CE0

extern u8 g_bInGameMenuCursor;         // 0x03005220: cursor row saved on exit
extern u32 g_dwInGameMenuReturnMode;   // 0x03005298: InGameMenu or InGameMenuFadeIn
extern u32 g_dwInGameMenuSubModeArg;   // 0x0300529C

extern void sub_08031FB8(u32 arg);
extern void BuildListMenu_candidate(const u8 *pDefinition);
extern void sub_080320A4(void);
extern void sub_0803217C(void);
extern void sub_080321A8(void);
extern void SelectInGameMenuEntry_candidate(void);
extern void sub_0803232C(void);
extern void sub_0803233C(void);
extern void sub_080323AC(void);
extern void sub_080323B0(void);
