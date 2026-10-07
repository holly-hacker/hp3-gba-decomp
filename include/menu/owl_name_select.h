#pragma once

#include "types.h"

// Game mode 0x42 (OwlNameSelect), the Owl Care Kit setup pushed by the GameCube link and
// connectivity screens. dwCurrentGameModeArg1 is the page: 0 picks the owl's name, 1 its type.
// dwModeScratchA is set once the page was left with B instead of A.
extern const u32 g_dwOwlNameSelectBg3Control;  // 0x08068BF8

extern void InitializeOwlNameSelect(void);
extern void UpdateOwlNameSelect(void);
extern void ExitOwlNameSelect(void);

extern void sub_08007434(u32 flags);  // clears DISPCNT bits
extern void sub_08030478(void);  // Left/Right: changes the highlighted name or type
extern void sub_08030594(void);  // creates the owl and arrow objects
extern void sub_080305F0(void);  // draws the page heading
extern void sub_08030644(void);  // draws the highlighted name or type
extern void sub_080306B8(void);  // A: confirms the page
extern void sub_080306F0(void);  // B: leaves the page
