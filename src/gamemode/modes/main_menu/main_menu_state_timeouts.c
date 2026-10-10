#include "types.h"
#include "menu/main_menu.h"

// Per-state threshold on dwModeTimer: UpdateMainMenu counts dwModeTimer up each call and skips
// the state body until it reaches the threshold. 0 means the state is not gated.
const u32 g_adwMainMenuStateTimeouts[6] = { 5, 5, 0, 0, 0, 0 };
