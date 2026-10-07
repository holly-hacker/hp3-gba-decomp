#pragma once

#include "types.h"
#include "graphics/object.h"

// Game mode 0x25 (UnusedHogwartsMapScreen), a list of nine entries drawn as sprites down the right
// edge, one 16-pixel row each. dwCurrentGameModeArg2 is the selected entry: Up/Down moves it and
// swaps in g_apUnusedHogwartsMapBackgrounds[entry]. B pushes the minigame difficulty select. No known
// code pushes this mode.
#define UNUSED_HOGWARTS_MAP_ENTRY_COUNT 9

extern const u8 *const g_apUnusedHogwartsMapBackgrounds[UNUSED_HOGWARTS_MAP_ENTRY_COUNT];  // 0x080629B8
extern const u32 g_dwUnusedHogwartsMapBg0Control;                                         // 0x080629DC
extern const u32 g_dwUnusedHogwartsMapBg1Control;                                         // 0x080629E0
extern const u32 g_dwUnusedHogwartsMapBg2Control;                                         // 0x080629E4
extern const u32 g_dwUnusedHogwartsMapBg3Control;                                         // 0x080629E8
extern const ObjectGfxRecord g_UnusedHogwartsMapEntryGfx;                                 // 0x080629EC

extern u32 g_dwUnusedHogwartsMapShownBg;  // 0x03003A50: entry whose background was loaded last
extern Object *g_pUnusedHogwartsMapCursor;  // 0x03003A54
extern void *g_pUnusedHogwartsMapBg1Tilemap;  // 0x03003A58: LoadBgGraphic result for BG1
extern Object *g_apUnusedHogwartsMapObjects[UNUSED_HOGWARTS_MAP_ENTRY_COUNT];  // 0x03003A60

extern void InitializeUnusedHogwartsMapScreen(void);
extern void UpdateUnusedHogwartsMapScreen(void);
extern void ExitUnusedHogwartsMapScreen(void);

extern void sub_080280CC(void);
extern void sub_080281AC(void);
extern void sub_08028240(void);
extern void sub_080282C4(void);
