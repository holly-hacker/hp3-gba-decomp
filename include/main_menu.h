#pragma once

#include "types.h"
#include "object.h"

typedef struct {
    Object *pCursorObject;         // 0x00
    u32 dwLoadGameAvailable;       // 0x04: 1 if a save slot can be loaded
} MainMenuState;

extern MainMenuState g_MainMenuState;  // 0x03005DB8
extern u32 g_dwMainMenuTextCursor;     // 0x03005DB0: next free text tile, after the copyright lines

extern void sub_0801DC6C(Object *pObject);

extern const u32 g_dwMainMenuBg3Control;
extern const u32 g_dwMainMenuBg2Control;
extern const u32 g_dwMainMenuBg1Control;
extern const u8 g_MainMenuBg2Graphic[];
extern const u8 *const g_apMainMenuTitleGraphic[8];
extern const u16 g_MainMenuPalette[];
extern const u32 g_adwMainMenuStateTimeouts[6];

extern void ResetSaveStateForNewGame_candidate(void);
extern u32 HasLoadableSaveSlot_candidate(void);
extern void sub_080438B4(void);
extern void DrawMainMenuCopyright_candidate(void);
extern void ShowMainMenuEntries_candidate(void);
extern void SelectMainMenuEntry_candidate(void);
extern void MoveMainMenuCursor_candidate(void);
