#pragma once

#include "types.h"
#include "actor.h"

// The title screen (MainMenu game mode): the copyright and "Press START"
// screen shown after boot, then the New Game / Load Game / Options /
// Mini-games list.

// Entry indices of the menu; also the cursor position in dwModeScratchB.
typedef enum {
    MainMenuNewGame   = 0,
    MainMenuLoadGame  = 1,
    MainMenuOptions   = 2,
    MainMenuMiniGames = 3,
} MainMenuEntry;

typedef struct {
    Actor *pCursorObject;         // 0x00
    u32 dwLoadGameAvailable;       // 0x04: 1 if a save slot can be loaded
    s32 nPaletteEffectSlot;  // 0x08: handle from StartPaletteEffectWithFrameCount, set by StartMainMenuPaletteEffect
} MainMenuState;

extern MainMenuState g_MainMenuState;  // 0x03005DB8
extern s32 g_nMainMenuTextCursor;     // 0x03005DB0: next free text tile, after the copyright lines

extern const u32 g_dwMainMenuBg3Control;
extern const u32 g_dwMainMenuBg2Control;
extern const u32 g_dwMainMenuBg1Control;
extern const u8 *const g_apMainMenuTitleGraphic[8];
extern const u32 g_adwMainMenuStateTimeouts[6];

void InitializeMainMenu(void);
void UpdateMainMenu(void);
void MoveMainMenuCursor(void);
void ExitMainMenuScreen(void);
void StartMainMenuPaletteEffect(void);
void ShowMainMenuEntries(void);
void DrawMainMenuEntry(u32 entry, u32 selectedEntry);
void DrawMainMenuCopyright(void);
void SelectMainMenuEntry(void);
u32 HasLoadableSaveSlot(void);
// Moves the cursor sprite beside the selected entry: tween nonzero glides it
// there over a few frames, zero places it at once.
void PositionMainMenuCursorObject(u32 tween);
