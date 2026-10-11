#pragma once

#include "types.h"
#include "actor.h"

// Result of the save slot screen, set by HandleSaveSlotInput_candidate.
typedef enum {
    SaveSlotResultConfirmed = 1,
    SaveSlotResultCancelled = 2,
} SaveSlotScreenResult;

extern u8 g_bSaveSlotScreenResult;  // 0x03005DC4

extern void ReleaseMenuCursor(Actor *pActor);
// Spawns a shared menu cursor sprite; kind selects its graphics and setup
// (4 the list cursor, 2 the quantity arrows, 0/1 dialog and loading screen).
extern Actor *SpawnMenuCursorActor(u32 kind);

extern void InitializeSaveSlotScreen_candidate(u32 titleStringId);
extern u32 HandleSaveSlotInput_candidate(void);
extern void SelectNewGameSlot_candidate(void);
extern void ResolveOverwriteConfirmation_candidate(void);
extern void ExitSaveSlotScreen_candidate(void);
extern void ConfirmLoadGameSlot_candidate(void);
extern void InitRoomState(void);

extern Actor *g_pMenuCursorActor;  // 0x03002E08
extern void InitializeMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection, const u8 *pOverlayGraphic, u32 overlayX, u32 overlayY);
extern void BeginMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection);
extern void sub_0801E0D8(void);
extern void ExitMenuScreen(void);
extern void SetMenuCursorPosition(Actor *pActor, s32 x, s32 y);  // SetActorPosition
