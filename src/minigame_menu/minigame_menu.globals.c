#include "types.h"
#include "minigame_menu.h"
#include "gen/graphics/minigames/hippogriff.h"

const u32 g_dwMinigameMenuBg3Control = 0x1C09;
const u32 g_dwMinigameMenuBg1Control = 0x9A06;

const u8 *const g_apMinigameMenuNumbers[4] = {
    gMinigameMenuNumber1,
    gMinigameMenuNumber2,
    gMinigameMenuNumber3,
    gMinigameMenuNumber4,
};

const u32 g_adwMinigameMenuNumberX[4] = { 7, 9, 13, 15 };
