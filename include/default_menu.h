#pragma once

#include "types.h"
#include "actor.h"

// The standard menu screen: frame on BG0, an optional overlay graphic on BG1 and the
// title and text on BG2, with a menu cursor and a pulsing selection color.

// cursorKind passed to BeginMenuScreen for a screen without a cursor.
#define MENU_SCREEN_NO_CURSOR 9

// BG1 is filled with this tile before the overlay graphic is drawn and when it is cleared.
#define MENU_SCREEN_OVERLAY_FILL_TILE 0x6F
// First BG1 tile of the overlay graphic.
#define MENU_SCREEN_OVERLAY_TILE_OFFSET 0x70

extern const u32 g_dwCommonBg0Control;  // BG0 control word, the menu frame
extern const u32 g_dwCommonBg1Control;  // BG1 control word, the overlay graphic
extern const u32 g_dwCommonBg2Control;  // BG2 control word, the text target for list menu rows

extern Actor *g_pMenuCursorActor;          // 0x03002E08: NULL when the screen has no cursor
extern s32 g_nMenuScreenPaletteEffectSlot;  // 0x03002E0C: selection pulse, -1 when none

extern void InitializeMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection,
                                 const u8 *pOverlayGraphic, u32 overlayX, u32 overlayY);
extern void LoadMenuScreenFrame(const u8 *pOverlayGraphic, u32 overlayX, u32 overlayY);
// Does nothing for a null graphic.
extern void LoadMenuScreenOverlay(const u8 *pGraphic, u32 x, u32 y);
extern void ClearMenuScreenOverlay(void);
extern void BeginMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection);
// Empty; called every frame by the menu screens' update functions.
extern void UpdateMenuScreen(void);
extern void ExitMenuScreen(void);
// Dialog string 0xACF (no text) leaves the title area blank.
extern void DrawMenuScreenTitle(u32 stringId);
