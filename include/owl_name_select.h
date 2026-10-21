#pragma once

#include "types.h"

// Game mode 0x42 (OwlNameSelect), the Owl Care Kit setup pushed by the GameCube link and
// connectivity screens. dwCurrentGameModeArg1 is the page: 0 picks the owl's name, 1 its type.
// dwModeScratchA is set once the page was left with B instead of A.
extern const u32 g_dwOwlNameSelectBg3Control;  // 0x08068BF8

extern void InitializeOwlNameSelect(void);
extern void UpdateOwlNameSelect(void);
extern void ExitOwlNameSelect(void);

extern void StepOwlNameSelectChoice(void);   // Left/Right: changes the highlighted name or type
extern void SpawnOwlNameSelectActors(void);  // the two arrows and the owl, menu icon slots 0-2
extern void DrawOwlNameSelectHeading(void);
extern void DrawOwlNameSelectChoice(void);   // the highlighted name or type
extern void ConfirmOwlNameSelectPage(void);  // A: the name page fades to the type page,
                                             // the type page opens the care screen
extern void CancelOwlNameSelectPage(void);   // B: leaves the page
