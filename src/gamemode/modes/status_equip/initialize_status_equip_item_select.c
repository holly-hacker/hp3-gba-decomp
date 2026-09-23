#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "status_equip.h"

void InitializeStatusEquipItemSelect(void)
{
    s32 i;

    g_StatusEquipItemSelect.awSavedPalette[0] = BG_PLTT[4];
    g_StatusEquipItemSelect.awSavedPalette[1] = BG_PLTT[5];
    g_StatusEquipItemSelect.awSavedPalette[2] = BG_PLTT[6];
    BG_PLTT[4] = 0x200;
    BG_PLTT[5] = 0;
    BG_PLTT[6] = 0xF;

    g_StatusEquipItemSelect.dwUnk18 = 0;
    for (i = 0; i < 3; i++)
        g_StatusEquipItemSelect.apStatArrows[i] = NULL;

    SetAlphaBlendTargets(0x14, 1);
    sub_080362D8();
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_GameModeStackContext.dwModeState = 1;
}
