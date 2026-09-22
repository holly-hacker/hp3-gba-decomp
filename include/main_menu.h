#pragma once

#include "types.h"
#include "object.h"

// Entry indices of the menu; also the cursor position in dwModeScratchB.
typedef enum {
    MainMenuNewGame   = 0,
    MainMenuLoadGame  = 1,
    MainMenuOptions   = 2,
    MainMenuMiniGames = 3,
} MainMenuEntry;

typedef struct {
    Object *pCursorObject;         // 0x00
    u32 dwLoadGameAvailable;       // 0x04: 1 if a save slot can be loaded
    s32 nPaletteEffectSlot_candidate;  // 0x08: handle from sub_0800D57C, set by sub_080438B4
} MainMenuState;

// Result of the save slot screen, set by HandleSaveSlotInput_candidate.
typedef enum {
    SaveSlotResultConfirmed = 1,
    SaveSlotResultCancelled = 2,
} SaveSlotScreenResult;

extern u8 g_bSaveSlotScreenResult;  // 0x03005DC4
extern MainMenuState g_MainMenuState;  // 0x03005DB8
extern u32 g_dwMainMenuTextCursor;     // 0x03005DB0: next free text tile, after the copyright lines

extern void sub_0801DC6C(Object *pObject);
extern Object *sub_0801D940(u32 kind);

extern const u32 g_dwMainMenuBg3Control;
extern const u32 g_dwMainMenuBg2Control;
extern const u32 g_dwMainMenuBg1Control;
extern const u8 g_MainMenuBg2Graphic[];
extern const u8 *const g_apMainMenuTitleGraphic[8];
extern const u16 g_MainMenuPalette[];
extern const u32 g_adwMainMenuStateTimeouts[6];

extern void ResetSaveStateForNewGame(void);
extern u32 HasLoadableSaveSlot(void);
extern void sub_080438B4(void);
extern void DrawMainMenuCopyright_candidate(void);
extern void ShowMainMenuEntries_candidate(void);
extern void SelectMainMenuEntry_candidate(void);
extern void MoveMainMenuCursor_candidate(void);
extern void DrawMainMenuEntry_candidate(u32 entry, u32 selectedEntry);
extern void PositionMainMenuCursorObject_candidate(u32 tween);

extern void InitializeSaveSlotScreen_candidate(u32 titleStringId);
extern u32 HandleSaveSlotInput_candidate(void);
extern void SelectNewGameSlot_candidate(void);
extern void ResolveOverwriteConfirmation_candidate(void);
extern void sub_0803227C(void);
extern void ExitSaveSlotScreen_candidate(void);
extern void ConfirmLoadGameSlot_candidate(void);
extern void InitRoomState(void);

extern Object *g_pMenuCursorObject;  // 0x03002E08
extern void sub_0801DF6C(u32 titleStringId, u32 arg1, u32 arg2, const u8 *pGraphic, u32 arg4, u32 arg5);
extern void sub_0801E0D8(void);
extern void sub_0801E0DC(void);
extern void sub_0801DCC4(Object *pObject, s32 x, s32 y);
