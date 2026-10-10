#pragma once

#include "types.h"

// Game mode 0x43 (QuantitySelectScreen): choose how many of g_dwItemUseItem to use. Left/Right
// change the quantity (dwModeScratchB, 1 up to the owned count), A confirms into
// g_dwItemUseQuantity and continues to ItemUseScreen, B returns to the character select.
extern void InitializeQuantitySelectScreen(void);
extern void UpdateQuantitySelectScreen(void);
extern void ExitQuantitySelectScreen(void);

extern void sub_08039428(void);  // builds the screen: header text, "Use how many?" prompt and arrows
extern void sub_0803950C(void);  // draws the quantity under the prompt
extern void sub_08039564(void);  // clears BG2 and frees the screen's objects
